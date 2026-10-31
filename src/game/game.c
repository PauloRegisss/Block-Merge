#include "game.h"

#include "raylib.h"

#include <stddef.h>

static int count_empty_cells(const Board *board) {
    int count = 0;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board->cells[row][col] == 0) {
                count++;
            }
        }
    }
    return count;
}

static void shuffle(int *values, int count) {
    for (int i = count - 1; i > 0; i--) {
        int j = GetRandomValue(0, i);
        int value = values[i];
        values[i] = values[j];
        values[j] = value;
    }
}

static bool offer_search(const Board *board, PieceOffer *offer, int depth) {
    if (depth == PIECE_OFFER_SIZE) {
        return true;
    }

    int shapes[PIECE_SHAPE_COUNT];
    int positions[BOARD_SIZE * BOARD_SIZE];
    for (int i = 0; i < PIECE_SHAPE_COUNT; i++) {
        shapes[i] = i;
    }
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        positions[i] = i;
    }
    shuffle(shapes, PIECE_SHAPE_COUNT);
    shuffle(positions, BOARD_SIZE * BOARD_SIZE);

    for (int shapeIndex = 0; shapeIndex < PIECE_SHAPE_COUNT; shapeIndex++) {
        Piece piece;
        if (!piece_create_from_shape(shapes[shapeIndex], &piece)) {
            continue;
        }

        for (int positionIndex = 0; positionIndex < BOARD_SIZE * BOARD_SIZE;
             positionIndex++) {
            int row = positions[positionIndex] / BOARD_SIZE;
            int col = positions[positionIndex] % BOARD_SIZE;
            if (!board_can_place(board, &piece, row, col)) {
                continue;
            }

            Board nextBoard = *board;
            board_place(&nextBoard, &piece, row, col);
            offer->pieces[depth] = piece;
            if (offer_search(&nextBoard, offer, depth + 1)) {
                return true;
            }
        }
    }

    return false;
}

bool offer_generate(const Board *board, PieceOffer *offer) {
    if (board == NULL || offer == NULL || count_empty_cells(board) < PIECE_OFFER_SIZE) {
        return false;
    }

    PieceOffer generated = {0};
    if (!offer_search(board, &generated, 0)) {
        return false;
    }

    *offer = generated;
    return true;
}

bool game_init(Game *game) {
    if (game == NULL) {
        return false;
    }

    Game initialized = {0};
    board_init(&initialized.board);
    if (!offer_generate(&initialized.board, &initialized.offer)) {
        initialized.game_over = true;
        *game = initialized;
        return false;
    }

    *game = initialized;
    return true;
}

int game_place_piece(Game *game, int offer_index, int row, int col) {
    if (game == NULL || game->game_over || offer_index < 0 ||
        offer_index >= PIECE_OFFER_SIZE || game->offer.used[offer_index] ||
        !board_can_place(&game->board, &game->offer.pieces[offer_index], row, col)) {
        return -1;
    }

    board_place(&game->board, &game->offer.pieces[offer_index], row, col);
    int clearedLines = board_clear_lines(&game->board);
    game->offer.used[offer_index] = true;

    bool offerComplete = true;
    bool hasPlayablePiece = false;
    for (int i = 0; i < PIECE_OFFER_SIZE; i++) {
        if (!game->offer.used[i]) {
            offerComplete = false;
            if (board_can_place_anywhere(&game->board, &game->offer.pieces[i])) {
                hasPlayablePiece = true;
            }
        }
    }

    if (!offerComplete && !hasPlayablePiece) {
        game->game_over = true;
    } else if (offerComplete) {
        PieceOffer nextOffer;
        if (!offer_generate(&game->board, &nextOffer)) {
            game->game_over = true;
        } else {
            game->offer = nextOffer;
        }
    }

    return clearedLines;
}
