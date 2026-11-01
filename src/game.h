#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "board.h"
#include "piece.h"
#include "screen.h"

#define TRAY_SIZE 3   // quantas peças aparecem por vez

typedef struct {
    Board board;
    Piece tray[TRAY_SIZE];   // as 3 peças disponíveis
    bool used[TRAY_SIZE];    // true = já foi colocada no tabuleiro
    int score;
    int dragging;            // índice da peça sendo arrastada, -1 = nenhuma
} Game;

void game_init(Game *game);
GameScreen game_update(Game *game);
void game_draw(const Game *game);

#endif