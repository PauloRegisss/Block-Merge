#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <raylib.h>
#include "screen.h"
#include "game.h"
#include "highscore.h"

GameScreen gameover_update(void);
void gameover_draw(const Game *game, const ScoreList *scores);

#endif