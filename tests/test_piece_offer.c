#include "game/board.h"
#include "game/game.h"

#include <assert.h>
#include <string.h>

static bool has_sequence(Board board, const PieceOffer *offer, int index) {
    if (index == PIECE_OFFER_SIZE) {
        return true;
    }

    const Piece *piece = &offer->pieces[index];
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board_can_place(&board, piece, row, col)) {
                Board next = board;
                board_place(&next, piece, row, col);
                if (has_sequence(next, offer, index + 1)) {
                    return true;
                }
            }
        }
    }
    return false;
}

static void assert_game_unchanged(const Game *game, const Game *before) {
    assert(game->game_over == before->game_over);
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            assert(game->board.cells[row][col] == before->board.cells[row][col]);
        }
    }
    for (int i = 0; i < PIECE_OFFER_SIZE; i++) {
        assert(game->offer.used[i] == before->offer.used[i]);
        for (int row = 0; row < PIECE_SIZE; row++) {
            for (int col = 0; col < PIECE_SIZE; col++) {
                assert(game->offer.pieces[i].shape[row][col] ==
                       before->offer.pieces[i].shape[row][col]);
            }
        }
        assert(game->offer.pieces[i].colorIndex == before->offer.pieces[i].colorIndex);
    }
}

static void test_game_init_and_rejected_placements(void) {
    Game game = {0};
    assert(!game_init(NULL));
    assert(game_init(&game));
    assert(!game.game_over);
    for (int i = 0; i < PIECE_OFFER_SIZE; i++) {
        assert(!game.offer.used[i]);
        assert(board_can_place_anywhere(&game.board, &game.offer.pieces[i]));
    }

    Game before = game;
    assert(game_place_piece(NULL, 0, 0, 0) == -1);
    assert_game_unchanged(&game, &before);
    assert(game_place_piece(&game, -1, 0, 0) == -1);
    assert_game_unchanged(&game, &before);
    assert(game_place_piece(&game, PIECE_OFFER_SIZE, 0, 0) == -1);
    assert_game_unchanged(&game, &before);
}

static void test_game_placement_refill_and_reuse(void) {
    Game game = {0};
    assert(game_init(&game));
    board_init(&game.board);
    for (int col = 0; col < BOARD_SIZE - 1; col++) {
        board_set(&game.board, 0, col, 1);
    }

    for (int i = 0; i < PIECE_OFFER_SIZE; i++) {
        assert(piece_create_from_shape(3, &game.offer.pieces[i]));
        game.offer.used[i] = false;
    }

    assert(game_place_piece(&game, 0, 0, BOARD_SIZE - 1) == 1);
    assert(game.offer.used[0]);
    assert(!game.game_over);

    Game before = game;
    assert(game_place_piece(&game, 0, 0, 0) == -1);
    assert_game_unchanged(&game, &before);
    assert(game_place_piece(&game, 1, -1, 0) == -1);
    assert_game_unchanged(&game, &before);

    assert(game_place_piece(&game, 1, 0, 0) == 0);
    assert(game.offer.used[1]);
    assert(game_place_piece(&game, 2, 0, 1) == 0);
    assert(!game.game_over);
    for (int i = 0; i < PIECE_OFFER_SIZE; i++) {
        assert(!game.offer.used[i]);
        assert(board_can_place_anywhere(&game.board, &game.offer.pieces[i]));
    }
}

static void test_game_over_when_remaining_pieces_do_not_fit(void) {
    Game game = {0};
    assert(game_init(&game));

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board_set(&game.board, row, col, 1);
        }
        board_set(&game.board, row, row, 0);
    }
    board_set(&game.board, 0, 1, 0);
    board_set(&game.board, 0, 2, 0);

    assert(piece_create_from_shape(6, &game.offer.pieces[0]));
    assert(piece_create_from_shape(7, &game.offer.pieces[1]));
    assert(piece_create_from_shape(3, &game.offer.pieces[2]));

    assert(game_place_piece(&game, 0, 0, 0) == 1);
    assert(!game.game_over);
    assert(!board_can_place_anywhere(&game.board, &game.offer.pieces[1]));
    assert(board_can_place_anywhere(&game.board, &game.offer.pieces[2]));

    assert(game_init(&game));
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board_set(&game.board, row, col, 1);
        }
        board_set(&game.board, row, row, 0);
    }
    board_set(&game.board, 0, 1, 0);
    board_set(&game.board, 0, 2, 0);
    assert(piece_create_from_shape(6, &game.offer.pieces[0]));
    assert(piece_create_from_shape(7, &game.offer.pieces[1]));
    assert(piece_create_from_shape(7, &game.offer.pieces[2]));

    assert(game_place_piece(&game, 0, 0, 0) == 1);
    assert(game.game_over);
    assert(game.offer.used[0]);
    assert(!board_can_place_anywhere(&game.board, &game.offer.pieces[1]));
    assert(!board_can_place_anywhere(&game.board, &game.offer.pieces[2]));
}

int main(void) {
    Board board;
    board_init(&board);

    PieceOffer offer = {0};
    assert(offer_generate(&board, &offer));
    assert(has_sequence(board, &offer, 0));
    for (int i = 0; i < PIECE_OFFER_SIZE; i++) {
        assert(!offer.used[i]);
    }

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            board_set(&board, row, col, 1);
        }
    }

    PieceOffer sentinel = {0};
    sentinel.pieces[0].shape[0][0] = 7;
    sentinel.used[1] = true;
    PieceOffer before = sentinel;
    assert(!offer_generate(&board, &sentinel));
    assert(memcmp(&sentinel, &before, sizeof(sentinel)) == 0);
    assert(!offer_generate(NULL, &sentinel));
    assert(memcmp(&sentinel, &before, sizeof(sentinel)) == 0);
    assert(!offer_generate(&board, NULL));

    test_game_init_and_rejected_placements();
    test_game_placement_refill_and_reuse();
    test_game_over_when_remaining_pieces_do_not_fit();
    return 0;
}
