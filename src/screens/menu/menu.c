#include "menu.h"
#include "fonts.h"
#include <raylib.h>
#define BUTTON_WIDTH 200.0f
#define BUTTON_HEIGHT 60.0f

static Rectangle get_start_button(void) {
    return (Rectangle){((float)GetScreenWidth() - BUTTON_WIDTH - 10) / 2.0f,
                       ((float)GetScreenHeight() - BUTTON_HEIGHT) / 2.0f, BUTTON_WIDTH,
                       BUTTON_HEIGHT};
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

    Rectangle button = get_start_button();
    DrawRectangleRec(button, (Color){255, 211, 89, 255});

    const char *text = "JOGAR";
    const float fontSize = 36.0f;
    const float spacing = 1.5f;

    Vector2 textSize = MeasureTextEx(FontRegular, text, fontSize, spacing);

    Vector2 textPosition = {button.x + (button.width - textSize.x) / 2.0f,
                            button.y + (button.height - textSize.y) / 2.0f};

    DrawTextEx(FontRegular, text, textPosition, fontSize, spacing, (Color){17, 24, 43, 255});
    // DrawRectangleRec(get_start_button(), (Color){255, 211, 89, 255});
    // Vector2 textSize = MeasureTextEx(FontRegular, "JOGAR", 100, 1.5f);

    // DrawTextEx(FontRegular, "JOGAR",
    //            (Vector2){get_start_button().x + (get_start_button().width - textSize.x) / 2.0f,
    //                      get_start_button().y + (get_start_button().height - textSize.y) / 2.0f},
    //            36.0f, 1.5f, (Color){17, 24, 43, 255});
}
