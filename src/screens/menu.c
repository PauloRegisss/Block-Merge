
#include "menu.h"
#include "screen.h"
#include "raylib.h"


static Rectangle startButton = { 300, 400, 200, 60 };

GameScreen menu_update(void)
{
    if (CheckCollisionPointRec(
            GetMousePosition(), startButton) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        return SCREEN_GAMEPLAY;
    }

    return SCREEN_MENU;
}

void menu_draw(void)
{
    ClearBackground((Color){ 50, 50, 50, 255 });

    DrawText("BLOCK MERGE", 250, 250, 40, RAYWHITE);

    DrawRectangleRounded(startButton, 0.3f, 8, BLUE);

    DrawText("Start", 365, 418, 30, WHITE);
}
