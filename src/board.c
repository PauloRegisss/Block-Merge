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

bool board_can_place(const Board *board, const Piece *piece, int row, int col) {
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            if (piece->shape[i][j] == 1 && !board_is_empty(board, row + i, col + j)) {
                return false;
            }
        }
    }
    return true;
}

void board_place(Board *board, const Piece *piece, int row, int col) {
    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            if (piece->shape[i][j] == 1) {
                board_set(board, row + i, col + j, 1);
            }
        }
    }
}

int board_clear_lines(Board *board) {
    bool linhaCheia[BOARD_SIZE];
    bool colunaCheia[BOARD_SIZE];
    int total = 0;

    // só descobre o que está cheio, sem alterar o board, presume que todos estejam cheios
    for (int i = 0; i < BOARD_SIZE; i++) {
        linhaCheia[i] = true;
        colunaCheia[i] = true;
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->cells[i][j] == 0) {
                linhaCheia[i] = false; // a linha i tem um buraco
                colunaCheia[j] = false; // a coluna j tem um buraco
            }
        }
    }

    // zera as linhas e colunas marcadas
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (linhaCheia[i] || colunaCheia[j]) {
                board->cells[i][j] = 0;
            }
        }
    }

    // Conta quantas linhas e colunas foram eliminadas
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (linhaCheia[i]) total++;
        if (colunaCheia[i]) total++;
    }

    return total;
}

bool board_can_place_anywhere(const Board *board, const Piece *piece) {
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board_can_place(board, piece, row, col)) {
                return true;
            }
        }
    }
    return false;
}