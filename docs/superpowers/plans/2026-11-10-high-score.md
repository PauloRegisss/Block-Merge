# Local High Score Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Persist each finished game's score in `highscores.txt` and show the best score on the menu and gameplay screens.

**Architecture:** Reuse `ScoreList` from `src/game/highscore.c`. Load it once in `main`, add/save the current score when gameplay transitions to game over, and pass its current best into the two draw functions.

**Tech Stack:** C11, CMake/CTest, raylib, existing `ScoreList` API.

**Spec:** `docs/superpowers/specs/2026-11-10-high-score-design.md`

## Global Constraints

- Keep the project at C11; do not add dependencies.
- Store scores in the working-directory file `highscores.txt`.
- Keep online ranking, reset/edit controls, and a full game-over screen out of scope.

## Review Focus

- First run with no file: best score is zero and the game continues normally (test missing-file load).
- Multiple saved scores: the highest score remains the displayed best after reload (test sorted round trip).
- File cannot be written: report persistence failure without crashing (test `scores_save` failure; main logs failure).
- One game-over transition: add/save the score once, not once per rendered frame (inspect transition guard in `main`).
- Shutdown: release the loaded score list (inspect cleanup path in `main`).

---

### Task 1: Test and integrate local score persistence

**Files:**
- Modify: `CMakeLists.txt` — add a CTest target for the existing high-score module.
- Create: `tests/test_highscore.c` — test missing-file load, score ordering/best, save-load round trip, and write failure; remove the temporary test file afterward.
- Modify: `src/main.c` — load `highscores.txt` once, persist the score on the guarded transition into `SCREEN_GAME_OVER`, log load/save failures, and free the list at shutdown.
- Modify: `src/screens/menu/menu.h`, `src/screens/menu/menu.c` — change `menu_draw` to accept the best score and draw it.
- Modify: `src/screens/gameplay/gameplay.h`, `src/screens/gameplay/gameplay.c` — change `gameplay_draw` to accept the best score and draw it beside/currently below the score.

**Interfaces:**
- Existing persistence API: `bool scores_load(ScoreList *list, const char *path)`, `bool scores_add(ScoreList *list, int score)`, `bool scores_save(const ScoreList *list, const char *path)`, `int scores_best(const ScoreList *list)`, and `void scores_free(ScoreList *list)` from `src/game/highscore.h`.
- New draw signatures: `void menu_draw(int best_score)` and `void gameplay_draw(const Game *game, int best_score)`.

- [x] **Step 1: Add the CTest target and write the persistence test.** Verify missing-file load gives an empty list/best `0`; add scores `20, 50, 10` and verify best `50`; save, reload, and verify count/order/best; verify saving under a nonexistent directory returns false. Use a test-local filename and remove it before and after the test.
- [x] **Step 2: Run the focused test and confirm the baseline.** Run `cmake -S . -B build -DBUILD_TESTING=ON`, `cmake --build build --target test_highscore`, then `ctest --test-dir build -R highscore --output-on-failure`. Expected: PASS against the existing persistence API.
- [x] **Step 3: Wire persistence into `main`.** Include `highscore.h`, initialize/load one `ScoreList` at startup, on the existing transition guard add `game.score` and save `highscores.txt`, report failures with `TraceLog`, use `scores_best` for drawing, and call `scores_free` before exit.
- [x] **Step 4: Display the best score.** Update both draw signatures and their only callers; render a Portuguese `RECORDE: %d` label on menu and gameplay.
- [x] **Step 5: Verify the complete build and test suite.** Run `cmake --build build` and `ctest --test-dir build --output-on-failure`; expected: build succeeds and all registered tests pass.
