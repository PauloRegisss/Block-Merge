#ifndef PIECE_H
#define PIECE_H

#include "raylib.h"

#define PIECE_SIZE 3   // a peça cabe em uma matriz 3x3

typedef struct{
    int shape[PIECE_SIZE][PIECE_SIZE];
    int colorIndex;
} Piece;

Piece piece_create_random(void);
Color piece_get_color(const Piece *piece);
void  piece_draw(const Piece *piece, int x, int y, int cellSize, int gap);
int piece_count_block(const Piece *piece);
int piece_height(const Piece *piece);

#endif
