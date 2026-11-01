#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "game.h"
#include "screen.h"

GameScreen gameplay_update(Game *game);
void gameplay_draw(const Game *game);

#endif