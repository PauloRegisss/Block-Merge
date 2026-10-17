#include "raylib.h"
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

void board_draw(const Board *board, int x, int y, int cellSize, int gap) { //troquei 8 por BOARD_SIZE
                                // os for ficam aqui dentro: a grade só é desenhada na tela JOGANDO
    for (int i = 0; i < BOARD_SIZE; i++) { 
        for (int j = 0; j < BOARD_SIZE; j++) {
            int cx = x + j * (cellSize + gap);
            int cy = y + i * (cellSize + gap);
            Color cor;
            if (board->cells[i][j] == 0) { // matriz é board.cells agr
                cor = (Color){100, 100, 100, 255};
            } else {
                cor = PURPLE;
            }

            DrawRectangle(cx, cy, cellSize, cellSize, cor);
        }
    }
}
