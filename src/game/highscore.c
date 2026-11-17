#include "highscore.h"

#include <stdio.h>
#include <stdlib.h>

// cria um nó novo com malloc; devolve NULL se faltar memória
static ScoreNode *node_create(int value) {
    ScoreNode *node = malloc(sizeof(ScoreNode));
    if (node == NULL) return NULL;
    node->value = value;
    node->next = NULL;
    return node;
}

// insere já na posição certa, mantendo a lista em ordem decrescente
bool scores_add(ScoreList *list, int score) {
    if (list == NULL) return false;

    ScoreNode *node = node_create(score);
    if (node == NULL) return false;

    if (list->head == NULL || score > list->head->value) {
        // vira o novo primeiro nó
        node->next = list->head;
        list->head = node;
    } else {
        // anda até o último nó que ainda é >= score e encaixa depois dele
        ScoreNode *current = list->head;
        while (current->next != NULL && current->next->value >= score) {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }

    list->count++;
    return true;
}

bool scores_load(ScoreList *list, const char *path) {
    if (list == NULL) return false;
    list->head = NULL;
    list->count = 0;

    FILE *file = fopen(path, "r");
    if (file == NULL) return true; // primeira vez: sem arquivo, lista vazia é normal

    int value;
    while (fscanf(file, "%d", &value) == 1) {
        if (!scores_add(list, value)) {
            fclose(file);
            scores_free(list);
            return false;
        }
    }
    fclose(file);
    return true;
}

bool scores_save(const ScoreList *list, const char *path) {
    if (list == NULL) return false;

    FILE *file = fopen(path, "w");
    if (file == NULL) return false;

    for (const ScoreNode *node = list->head; node != NULL; node = node->next) {
        fprintf(file, "%d\n", node->value);
    }
    fclose(file);
    return true;
}

int scores_best(const ScoreList *list) {
    if (list == NULL || list->head == NULL) return 0;
    return list->head->value; // o maior fica sempre na frente
}

// percorre a lista dando free em cada nó
void scores_free(ScoreList *list) {
    if (list == NULL) return;

    ScoreNode *node = list->head;
    while (node != NULL) {
        ScoreNode *next = node->next; // guarda o próximo antes de liberar
        free(node);
        node = next;
    }
    list->head = NULL;
    list->count = 0;
}
