#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#define BOARD_SIZE 8

typedef struct {
    int cells[BOARD_SIZE][BOARD_SIZE]; // 0 = vazio, 1 = ocupado
} Board;

void board_init(Board *board);
bool board_in_bounds(int row, int col);
bool board_is_empty(const Board *board, int row, int col);
void board_set(Board *board, int row, int col, int value);
void board_draw(const Board *board, int x, int y, int cellSize, int gap);
#endif
