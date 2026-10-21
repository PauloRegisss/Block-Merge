#include "fonts.h"
#include "menu.h"
#include "raylib.h"
#include "screen.h"
#include "board.h"
#define ESPACO 4

int main(void) {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

    InitWindow(800, 600, "Block Merge");
    InitAudioDevice();                                    
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
    Board board;
    board_init(&board);
    board_set(&board, 6, 7, 1); // desenho na matriz no canto inferior

    // preenche a linha 7 inteira para testar a eliminação
    for (int j = 0; j < BOARD_SIZE; j++) {
        board_set(&board, 7, j, 1);
    }

    int eliminadas = board_clear_lines(&board);
    (void)eliminadas;

    while (!WindowShouldClose()) {
        UpdateMusicStream(musicaFundo);                       
        GameScreen telaAnterior = screen;                     

        switch (screen) {
            case SCREEN_MENU:
                screen = menu_update();
                break;
            case SCREEN_GAMEPLAY:                          
                if (IsKeyPressed(KEY_G)) screen = SCREEN_GAME_OVER;
                break;
            default:
                break;
        }
        if(telaAnterior == SCREEN_MENU && screen == SCREEN_GAMEPLAY){   
            PlayMusicStream(musicaFundo);
        }
        if(telaAnterior != SCREEN_GAME_OVER && screen == SCREEN_GAME_OVER){  
            StopMusicStream(musicaFundo);
        }
        BeginDrawing();
        ClearBackground((Color){17, 24, 43, 255});

        Vector2 textSize = MeasureTextEx(FontRegular, "© 2026 Block Merge", 16.0f, 1.0f);
        DrawTextEx(FontRegular, "© 2026 Block Merge",
                   (Vector2){(float)GetScreenWidth() - textSize.x - 16.0f,
                             (float)GetScreenHeight() - textSize.y - 16.0f},
                   16.0f, 1.0f, (Color){140, 150, 170, 160});
        switch (screen) {
            case SCREEN_MENU:
                menu_draw();
                break;
            case SCREEN_GAMEPLAY: {
                int cellSize = 60;
                int larguraGrade = BOARD_SIZE * cellSize + (BOARD_SIZE - 1) * ESPACO;
                int origemX = (GetScreenWidth() - larguraGrade) / 2;
                int origemY = 40;
                board_draw(&board, origemX, origemY, cellSize, ESPACO);
                break;                                       
            }
            default:
                break;
}

        EndDrawing();
    }
    UnloadFonts();
    UnloadMusicStream(musicaFundo);                          
    CloseAudioDevice();                                       
    CloseWindow();
    return 0;
}