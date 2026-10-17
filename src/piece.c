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

#define SHAPE_COUNT 16


static const int SHAPES[SHAPE_COUNT][PIECE_SIZE][PIECE_SIZE] = {
    // 0. Quadrado 2x2
    {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 0},
    },

    // 1. Linha horizontal 3
    {
        {1, 1, 1},
        {0, 0, 0},
        {0, 0, 0},
    },

    // 2. L
    {
        {1, 0, 0},
        {1, 0, 0},
        {1, 1, 0},
    },

    // 3. Bloco unitário
    {
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    },

    // 4. Linha vertical 3
    {
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
    },

    // 5. T vertical
    {
        {1, 1, 1},
        {0, 1, 0},
        {0, 1, 0},
    },

    // 6. Linha horizontal 2
    {
        {1, 1, 0},
        {0, 0, 0},
        {0, 0, 0},
    },

    // 7. Linha horizontal 4 (limitada a 3x3: usar matriz maior)
    {
        {1, 1, 1},
        {0, 0, 0},
        {0, 0, 0},
    },

    // 8. Quadrado 3x3
    {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1},
    },

    // 9. L invertido
    {
        {0, 1, 0},
        {0, 1, 0},
        {1, 1, 0},
    },

    // 10. L espelhado
    {
        {1, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
    },

    // 11. Z
    {
        {1, 1, 0},
        {0, 1, 1},
        {0, 0, 0},
    },

    // 12. S
    {
        {0, 1, 1},
        {1, 1, 0},
        {0, 0, 0},
    },

    // 13. T clássico
    {
        {1, 1, 1},
        {0, 1, 0},
        {0, 0, 0},
    },

    // 14. L pequeno
    {
        {1, 0, 0},
        {1, 1, 0},
        {0, 0, 0},
    },

    // 15. J pequeno
    {
        {0, 1, 0},
        {0, 1, 1},
        {0, 0, 0},
    },
};

Piece piece_create_random(void) {
    Piece piece;
    int s = GetRandomValue(0, SHAPE_COUNT - 1); // valor aleatorio de 0 a 15

    for (int i = 0; i < PIECE_SIZE; i++) {
        for (int j = 0; j < PIECE_SIZE; j++) {
            piece.shape[i][j] = SHAPES[s][i][j];
        }
    }

    piece.colorIndex = GetRandomValue(0, PALETTE_COUNT - 1); // gera um valor aleatorio
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

//A função recebe uma peça e devolve quantos 1 existem na matriz dela. O quadrado 2x2 devolve 4, o L devolve 4, o ponto devolve 1

int piece_count_blocks(const Piece *piece){  
    int total = 0;

    for(int i = 0; i < PIECE_SIZE; i++){
        for(int j = 0; j < PIECE_SIZE; j++){
            if(piece->shape[i][j] == 1){
                total++;
            }
        }
    }
    return total;
}

//Quem for centralizar a peça na tela ou no mouse durante o arrasto vai precisar desses números.

int piece_height(const Piece *piece){     
    int maxRow = -1;

    for(int i = 0; i < PIECE_SIZE; i++){
        for(int j = 0; j < PIECE_SIZE; j++){
            if(piece->shape[i][j] == 1 && i > maxRow){
                maxRow = i;
            }
        }
    }
    return maxRow + 1;
}