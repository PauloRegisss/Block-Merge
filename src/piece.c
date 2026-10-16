#include "piece.h"

#define PALETTE_COUNT 4

// As cores do design.pen: mint, yellow, coral, sky
static const Color PALETTE[PALETTE_COUNT] = {
    {91, 232, 180, 255},  // índice 0: mint
    {255, 211, 90, 255},  // índice 1: yellow
    {255, 113, 108, 255}, // índice 2: coral
    {101, 190, 255, 255}, // índice 3: sky
};

Piece piece_create(void) {
    Piece piece = {
        .shape =
            {
                {1, 0, 0},
                {1, 0, 0},
                {1, 1, 0},
            },
        .colorIndex = 0,
    };
    return piece;
}

Color piece_get_color(const Piece *piece) {
    return PALETTE[piece->colorIndex];
}

#define SHAPE_COUNT 4

static const int SHAPES[SHAPE_COUNT][PIECE_SIZE][PIECE_SIZE] = {
    {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 0},
    },
    {
        {1, 1, 1},
        {0, 0, 0},
        {0, 0, 0},
    },
    {
        {1, 0, 0},
        {1, 0, 0},
        {1, 1, 0},
    },
    {
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    },
    {
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
    },
    {
        {1, 1, 1},
        {0, 1, 0},
        {0, 1, 0},
    },
};

Piece piece_create_random(void) {
    Piece piece;
    int s = GetRandomValue(0, SHAPE_COUNT - 1); // valor aleatorio de 0 a 5

    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            piece.shape[i][j] = SHAPES[s][i][j];
        }
    }

    piece.colorIndex = GetRandomValue(0, PALETTE_COUNT - 1); // valor aleatorio de 0 a 5
    return piece;
}

void piece_draw(const Piece *piece, int x, int y, int cellSize, int gap) {
    Color cor = piece_get_color(piece);

    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            if (piece->shape[i][j] == 1) {
                DrawRectangle(x + j * (cellSize + gap), y + i * (cellSize + gap), cellSize,
                              cellSize, cor);
            }
        }
    }
}
