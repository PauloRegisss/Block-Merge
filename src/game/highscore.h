#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdbool.h>

typedef struct {
    int *values;     // array alocado dinamicamente
    int count;       // quantas pontuações existem
    int capacity;    // quantas cabem antes de precisar de realloc
} ScoreList;

bool scores_add(ScoreList *list, int score);
bool scores_load(ScoreList *list, const char *path);

#endif