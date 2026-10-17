#include "fonts.h"
#include "menu.h"
#include "raylib.h"
#include "screen.h"
#define ESPACO 4

int main(void) {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

    int monitor = GetCurrentMonitor();
    int screenWidth = GetMonitorWidth(monitor);
    int screenHeight = GetMonitorHeight(monitor);

    InitWindow(screenWidth, screenHeight, "Block Merge");
    SetTargetFPS(60);
    LoadFonts();
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

    while (!WindowShouldClose()) {

        switch (screen) {
            case SCREEN_MENU:
                screen = menu_update();
                break;
        }
        BeginDrawing();
        ClearBackground((Color){17, 24, 43, 255});

        Vector2 textSize = MeasureTextEx(FontRegular, "© 2026 Block Merge", 16.0f, 1.0f);
        DrawTextEx(FontRegular, "@ 2026 Block Merge",
                   (Vector2){(float)GetScreenWidth() - textSize.x - 16.0f,
                             (float)GetScreenHeight() - textSize.y - 16.0f},
                   16.0f, 1.0f, (Color){140, 150, 170, 160});
        switch (screen) {
            case SCREEN_MENU:
                menu_draw();
                break;
        }
        // } else {
        //   // os for ficam aqui dentro: a grade só é desenhada na tela JOGANDO
        //   for (int i = 0; i < BOARD_SIZE; i++){       //troquei 8 por BOARD_SIZE
        //     for (int j = 0; j < BOARD_SIZE; j++){     //troquei 8 por BOARD_SIZE
        //       int x = origemX +  j * (TAMANHO_CELULA + ESPACO);
        //       int y = origemY + i * (TAMANHO_CELULA+ ESPACO);

        //       Color cor;

        //       if(board.cells[i][j] == 0){ //troquei matriz por board.cells
        //         cor = (Color) {100, 100, 100, 255};
        //       } else{
        //         cor = PURPLE;
        //       }
        //       DrawRectangle(x, y, TAMANHO_CELULA, TAMANHO_CELULA, cor);
        //     }
        //   }
        // }

        EndDrawing();
    }
    UnloadFonts();
    CloseWindow();

    return 0;
}
