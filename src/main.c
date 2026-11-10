#include <time.h>
#include "fonts.h"
#include "menu.h"
#include "raylib.h"
#include "screen.h"
#include "game.h"
#include "gameplay.h"
#include "highscore.h"

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
    Game game;
    const char *highscoresPath = "highscores.txt";
    ScoreList scores = {0};
    bool scoresLoaded = scores_load(&scores, highscoresPath);
    if (!scoresLoaded) {
        TraceLog(LOG_ERROR, "Nao foi possivel carregar %s", highscoresPath);
    }
    /*
    Rectangle bottom; // declarei uma variavel bottom do tipo Rectangle
                       // (retangulo)
    bottom = (Rectangle){(WINDOW_WIDTH - 200) / 2, 400, 200, 60};

    Board board;        // troquei a int matriz[8][8]
    board_init(&board); // & = "passa o endereço do board"
    board_set(&board, 6, 7, 1);
    int larguraGrade = BOARD_SIZE * TAMANHO_CELULA + (BOARD_SIZE - 1) * ESPACO;
    int origemX = (WINDOW_WIDTH - larguraGrade) / 2;
    int origemY = 40;*/

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
            default:
                break;
        }
        if (telaAnterior == SCREEN_MENU && screen == SCREEN_GAMEPLAY) {
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
