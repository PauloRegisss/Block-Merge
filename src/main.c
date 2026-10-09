#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int main(void) {
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Block Merge");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground((Color){24, 26, 35, 255});

    DrawText("Block TESTE", 300, 350, 40, RAYWHITE);

    DrawText("Pressione ESC para sair", 290, 410, 20, LIGHTGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
