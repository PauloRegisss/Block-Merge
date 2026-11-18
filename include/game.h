#ifndef GAME_H
#define GAME_H

#include "board.h"

#include <stdbool.h>

#define PIECE_OFFER_SIZE 3

typedef struct {
    Piece pieces[PIECE_OFFER_SIZE];
    bool used[PIECE_OFFER_SIZE];
} PieceOffer;

typedef struct {
    Board board;
    PieceOffer offer;
    int score;
    bool game_over;
} Game;

bool offer_generate(const Board *board, PieceOffer *offer);
bool game_init(Game *game);
int game_place_piece(Game *game, int offer_index, int row, int col);

#endif