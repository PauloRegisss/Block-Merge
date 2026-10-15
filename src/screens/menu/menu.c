#include "menu.h"
#include "fonts.h"
#include <raylib.h>
static Rectangle startButton = {300, 400, 200, 60};

GameScreen menu_update(void) {
    if (CheckCollisionPointRec(GetMousePosition(), startButton) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return SCREEN_GAMEPLAY;
    }

    return SCREEN_MENU;
}

void menu_draw(void) {
    ClearBackground((Color){17, 24, 43, 255});

    DrawTextEx(FontTitle, "BLOCK", (Vector2){280, 200}, 150, 1.5f, RAYWHITE);
    DrawTextEx(FontTitle, "MERGE", (Vector2){280, 300}, 150, 1.5f, (Color){90, 232, 180, 255});

    // DrawRectangleRounded(FontTitle, startButton, 0.3f, 8, BLUE);

    DrawText("Start", 365, 418, 30, WHITE);
}
