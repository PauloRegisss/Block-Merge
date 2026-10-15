#include "board.h"

void board_init(Board *board){
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            board->cells[i][j] = 0;
        }
    }
}

bool board_in_bounds(int row, int col){
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

bool board_is_empty(const Board *board, int row, int col){
    if(!board_in_bounds(row, col)){
        return false;
    }
    return board->cells[row][col] == 0;
}

void board_set(Board *board, int row, int col, int value) {
    if(board_in_bounds(row, col)){
        board->cells[row][col] = value;
    }
}
