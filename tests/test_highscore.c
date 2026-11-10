#include "highscore.h"

#include <assert.h>
#include <stdio.h>

int main(void) {
    const char *path = "test_highscores.tmp";
    remove(path);

    ScoreList scores;
    assert(scores_load(&scores, path));
    assert(scores.count == 0);
    assert(scores_best(&scores) == 0);
    assert(scores_add(&scores, 20));
    assert(scores_add(&scores, 50));
    assert(scores_add(&scores, 10));
    assert(scores_best(&scores) == 50);
    assert(scores_save(&scores, path));
    scores_free(&scores);

    ScoreList loaded;
    assert(scores_load(&loaded, path));
    assert(loaded.count == 3);
    assert(loaded.values[0] == 50);
    assert(loaded.values[1] == 20);
    assert(loaded.values[2] == 10);
    assert(scores_best(&loaded) == 50);
    assert(!scores_save(&loaded, "highscore_test_no_such_dir/scores.txt"));
    scores_free(&loaded);

    remove(path);
    return 0;
}
