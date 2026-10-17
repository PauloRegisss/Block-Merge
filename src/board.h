#ifndef BOARD_H
#define BOARD_H

#include "piece.h" // trabalhar com a struct Piece e PIECE_SIZE
#include <stdbool.h>

#define BOARD_SIZE 8


typedef struct {
    int cells[BOARD_SIZE][BOARD_SIZE]; // 0 = vazio, 1 = ocupado
} Board;

void board_init(Board *board); // percorre os 64 blocos e zera todos, modifica o board original
bool board_in_bounds(int row, int col); // 
bool board_is_empty(const Board *board, int row, int col);
void board_set(Board *board, int row, int col, int value);
void board_draw(const Board *board, int x, int y, int cellSize, int gap);

bool board_can_place(const Board *board, const Piece *piece, int row, int col);
void board_place(Board *board, const Piece *piece, int row, int col);
int board_clear_lines(Board *board);
bool board_can_place_anywhere(const Board *board, const Piece *piece);

#endif
