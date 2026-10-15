#include "raylib.h"
#include "board.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define TAMANHO_CELULA 60   //numeros da grade
#define ESPACO 4

typedef enum {MENU, JOGANDO} Tela; // lista de numeros com nome "Tela"

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Block Merge");
  SetWindowPosition(100, 100); //move a janela pra um ponto fixo da tela
  SetTargetFPS(60);

  Tela tela = MENU; // inicia o jogo no menu 

  Rectangle bottom; //declarei uma variavel bottom do tipo Rectangle (retangulo)
  bottom = (Rectangle) { (WINDOW_WIDTH - 200) / 2, 400, 200, 60 };

  Board board; //troquei a int matriz[8][8]
  board_init(&board);          // & = "passa o endereço do board"
  board_set(&board, 2, 2, 0);
  int larguraGrade = BOARD_SIZE * TAMANHO_CELULA + (BOARD_SIZE - 1) * ESPACO;
  int origemX = (WINDOW_WIDTH - larguraGrade) / 2;
  int origemY = 40;

  while (!WindowShouldClose()) {

    if (tela == MENU){
      if (CheckCollisionPointRec(GetMousePosition(), bottom) &&
          IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
          tela = JOGANDO;
      }
    }

    BeginDrawing();
    ClearBackground((Color){50, 50, 50, 255});

    if(tela == MENU){
        DrawRectangleRounded(bottom, 0.3f, 8, BLUE);
        DrawText("Start", 
                bottom.x + (bottom.width - MeasureText("Start", 30)) / 2,
                bottom.y + (bottom.height - 30) / 2,
                30, WHITE);
        DrawText("Block Merge TESTE", 300, 350, 40, RAYWHITE);
        DrawText("Pressione ESC para sair", 290, 500, 20, LIGHTGRAY);

    } else {
      // os for ficam aqui dentro: a grade só é desenhada na tela JOGANDO
      for (int i = 0; i < BOARD_SIZE; i++){       //troquei 8 por BOARD_SIZE
        for (int j = 0; j < BOARD_SIZE; j++){     //troquei 8 por BOARD_SIZE
          int x = origemX +  j * (TAMANHO_CELULA + ESPACO);
          int y = origemY + i * (TAMANHO_CELULA+ ESPACO);

          Color cor;

          if(board.cells[i][j] == 0){ //troquei matriz por board.cells
            cor = (Color) {100, 100, 100, 255};
          } else{
            cor = PURPLE;
          }
          DrawRectangle(x, y, TAMANHO_CELULA, TAMANHO_CELULA, cor);
        }
      }
    }

    EndDrawing();

  }

  CloseWindow();

  return 0;
}