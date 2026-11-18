#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdbool.h>

// um nó da lista encadeada: guarda uma pontuação e aponta para a próxima
typedef struct ScoreNode {
    int value;
    struct ScoreNode *next;
} ScoreNode;

typedef struct {
    ScoreNode *head; // maior pontuação (lista ordenada em ordem decrescente)
    int count;       // quantos nós existem
} ScoreList;

bool scores_load(ScoreList *list, const char *path);
bool scores_add(ScoreList *list, int score);
bool scores_save(const ScoreList *list, const char *path);
int  scores_best(const ScoreList *list);
void scores_free(ScoreList *list);

#endif