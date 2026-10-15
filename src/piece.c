#include "piece.h"

#define PALETTE_COUNT 4

// As cores do design.pen: mint, yellow, coral, sky
static const Color PALETTE[PALETTE_COUNT] = {
    {91, 232, 180, 255},   // índice 0: mint
    {255, 211, 90, 255},   // índice 1: yellow
    {255, 113, 108, 255},  // índice 2: coral
    {101, 190, 255, 255},  // índice 3: sky
};

Piece piece_create(void) {
    Piece piece = {
        .shape = {
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
    { // 0: quadrado 2x2
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 0},
    },
    { // 1: linha horizontal de 3
        {1, 1, 1},
        {0, 0, 0},
        {0, 0, 0},
    },
    { // 2: L
        {1, 0, 0},
        {1, 0, 0},
        {1, 1, 0},
    },
    { // 3: ponto único
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    },
};