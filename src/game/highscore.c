#include "highscore.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 8

static int compare_desc(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return y - x;   // maior primeiro
}

bool scores_add(ScoreList *list, int score) {
    if (list == NULL) return false;

    if (list->count == list->capacity) {
        int newCapacity = (list->capacity == 0) ? INITIAL_CAPACITY : list->capacity * 2;
        int *bigger = realloc(list->values, (size_t)newCapacity * sizeof(int));
        if (bigger == NULL) return false;   // o array antigo continua válido
        list->values = bigger;
        list->capacity = newCapacity;
    }

    list->values[list->count++] = score;
    qsort(list->values, (size_t)list->count, sizeof(int), compare_desc);
    return true;
}

bool scores_load(ScoreList *list, const char *path) {
    if (list == NULL) return false;
    list->values = NULL;
    list->count = 0;
    list->capacity = 0;

    FILE *file = fopen(path, "r");
    if (file == NULL) return true;   // primeira vez: sem arquivo, lista vazia é normal

    int value;
    while (fscanf(file, "%d", &value) == 1) {
        if (!scores_add(list, value)) {
            fclose(file);
            return false;
        }
    }
    fclose(file);
    return true;
}