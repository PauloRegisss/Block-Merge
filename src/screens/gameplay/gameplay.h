#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"
#include "board.h"
#include "piece.h"
#include "game.h"
#include "screen.h"

GameScreen gameplay_update(Game *game, Sound placement_sound);
void gameplay_draw(const Game *game, int best_score);

#endif
