#include <time.h>
#include "fonts.h"
#include "menu.h"
#include "raylib.h"
#include "screen.h"
#include "game.h"
#include "gameplay.h"
#include "highscore.h"
#include "gameover.h"

int main(void) {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

    InitWindow(800, 600, "Block Merge");
    SetRandomSeed((unsigned int)time(NULL));
    InitAudioDevice();
    Sound placementSound = LoadSound("assets/audio/place.wav");
    if (!IsSoundValid(placementSound)) {
        TraceLog(LOG_ERROR, "Nao foi possivel carregar assets/audio/place.wav");
    }
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    SetWindowPosition(0, 0);

    SetTargetFPS(60);
    LoadFonts();

    Music musicaFundo = LoadMusicStream("assets/audio/musica_fundo.wav");
    musicaFundo.looping = true;
    SetMusicVolume(musicaFundo, 0.8f);
    TraceLog(LOG_INFO, "musica valida: %d", IsMusicValid(musicaFundo));

    GameScreen screen = SCREEN_MENU;
    Game game = {0};
    const char *highscoresPath = "highscores.txt";
    ScoreList scores = {0};
    bool scoresLoaded = scores_load(&scores, highscoresPath);
    if (!scoresLoaded) {
        TraceLog(LOG_ERROR, "Nao foi possivel carregar %s", highscoresPath);
    }

    while (!WindowShouldClose()) {
        UpdateMusicStream(musicaFundo);
        GameScreen telaAnterior = screen;

        switch (screen) {
            case SCREEN_MENU:
                screen = menu_update();
                break;
            case SCREEN_GAMEPLAY:
                screen = gameplay_update(&game, placementSound);
                break;
            case SCREEN_GAME_OVER:
                screen = gameover_update();
                break;
            default:
                break;
        }

        if ((telaAnterior == SCREEN_MENU || telaAnterior == SCREEN_GAME_OVER) &&
            screen == SCREEN_GAMEPLAY) {
            game_init(&game);
            PlayMusicStream(musicaFundo);
        }

        if (telaAnterior != SCREEN_GAME_OVER && screen == SCREEN_GAME_OVER) {
            StopMusicStream(musicaFundo);
            if (scoresLoaded) {
                if (!scores_add(&scores, game.score)) {
                    TraceLog(LOG_ERROR, "Nao foi possivel adicionar a pontuacao ao recorde");
                } else if (!scores_save(&scores, highscoresPath)) {
                    TraceLog(LOG_ERROR, "Nao foi possivel salvar %s", highscoresPath);
                }
            }
        }

        BeginDrawing();
        ClearBackground((Color){17, 24, 43, 255});

        Vector2 textSize = MeasureTextEx(FontRegular, "(c) 2026 Block Merge", 16.0f, 1.0f);
        DrawTextEx(FontRegular, "(c) 2026 Block Merge",
                   (Vector2){(float)GetScreenWidth() - textSize.x - 16.0f,
                             (float)GetScreenHeight() - textSize.y - 16.0f},
                   16.0f, 1.0f, (Color){140, 150, 170, 160});

        switch (screen) {
            case SCREEN_MENU:
                menu_draw(scores_best(&scores));
                break;
            case SCREEN_GAMEPLAY:
                gameplay_draw(&game, scores_best(&scores));
                break;
            case SCREEN_GAME_OVER:
                gameplay_draw(&game, scores_best(&scores));
                gameover_draw(&game, &scores);
                break;
            default:
                break;
        }

        EndDrawing();
    }

    scores_free(&scores);
    UnloadFonts();
    UnloadMusicStream(musicaFundo);
    if (IsSoundValid(placementSound)) UnloadSound(placementSound);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
