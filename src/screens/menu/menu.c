#include "menu.h"
#include "fonts.h"
#include <raylib.h>
#define START_BUTTON_WIDTH 200.0f
#define START_BUTTON_HEIGHT 60.0f
#define HOW_BUTTON_WIDTH 200.0f
#define HOW_BUTTON_HEIGHT 60.0f
static Rectangle get_start_button(void) {
    return (Rectangle){((float)GetScreenWidth() - START_BUTTON_WIDTH - 10) / 2.0f,
                       ((float)GetScreenHeight() - START_BUTTON_HEIGHT) / 2.0f, START_BUTTON_WIDTH,
                       START_BUTTON_HEIGHT};
}
static Rectangle get_how_to_play_button(void) {
    return (Rectangle){((float)GetScreenWidth() - HOW_BUTTON_WIDTH - 10) / 2.0f,
                       ((float)GetScreenHeight() - HOW_BUTTON_HEIGHT + 180) / 2.0f,
                       HOW_BUTTON_WIDTH, HOW_BUTTON_HEIGHT};
}
GameScreen menu_update(void) {
    if (CheckCollisionPointRec(GetMousePosition(), get_start_button()) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return SCREEN_GAMEPLAY;
    }

    return SCREEN_MENU;
}

void menu_draw(void) {
    ClearBackground((Color){17, 24, 43, 255});

    DrawTextEx(
        FontTitle, "BLOCK",
        (Vector2){(float)(GetScreenWidth() - 260) / 2.0f, (float)(GetScreenHeight() - 600) / 2.0f},
        150, 1.5f, RAYWHITE);
    DrawTextEx(
        FontTitle, "MERGE",
        (Vector2){(float)(GetScreenWidth() - 280) / 2.0f, (float)(GetScreenHeight() - 410) / 2.0f},
        150, 1.5f, (Color){90, 232, 180, 255});

    Rectangle start_button = get_start_button();
    DrawRectangleRounded(start_button, 0.2f, 4, (Color){255, 211, 89, 255});

    Vector2 textSize = MeasureTextEx(FontRegular, "JOGAR", 25.0f, 1.5f);
    Vector2 textPosition = {start_button.x + (start_button.width - textSize.x) / 2.0f,
                            start_button.y + (start_button.height - textSize.y) / 2.0f};
    DrawTextEx(FontRegular, "JOGAR", textPosition, 25.0f, 1.5f, (Color){17, 24, 43, 255});
    Rectangle how_button = get_how_to_play_button();
    DrawRectangleRounded(how_button, 0.2f, 4, (Color){17, 24, 43, 255});
    DrawRectangleRoundedLinesEx(how_button, 0.2f, 4, 2.0f, (Color){247, 242, 233, 102});

    Vector2 howtextSize = MeasureTextEx(FontRegular, "COMO JOGAR", 25.0f, 1.5f);
    Vector2 howtextPosition = {how_button.x + (how_button.width - howtextSize.x) / 2.0f,
                               how_button.y + (how_button.height - howtextSize.y) / 2.0f};
    DrawTextEx(FontRegular, "COMO JOGAR", howtextPosition, 25.0f, 1.5f, WHITE);
    // DrawRectangleRec(get_start_button(), (Color){255, 211, 89, 255});
    // Vector2 textSize = MeasureTextEx(FontRegular, "JOGAR", 100, 1.5f);

    // DrawTextEx(FontRegular, "JOGAR",
    //            (Vector2){get_start_button().x + (get_start_button().width - textSize.x) / 2.0f,
    //                      get_start_button().y + (get_start_button().height - textSize.y) / 2.0f},
    //            36.0f, 1.5f, (Color){17, 24, 43, 255});
}
