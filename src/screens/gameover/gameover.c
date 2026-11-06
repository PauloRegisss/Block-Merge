#include "gameover.h"

#include "fonts.h"
#include "raylib.h"

#define BTN_W 280.0f
#define BTN_H 58.0f

// botão 0 = jogar de novo, botão 1 = menu (um abaixo do outro, centralizados)
static Rectangle button_rect(int index) {
    float x = ((float)GetScreenWidth() - BTN_W) / 2.0f;
    float y = (float)GetScreenHeight() / 2.0f + 20.0f + (float)index * 76.0f;
    return (Rectangle){x, y, BTN_W, BTN_H};
}

static void draw_centered(const char *text, float size, float y, Color color) {
    Vector2 s = MeasureTextEx(FontRegular, text, size, 1.0f);
    DrawTextEx(FontRegular, text,
               (Vector2){((float)GetScreenWidth() - s.x) / 2.0f, y}, size, 1.0f, color);
}

static void draw_button(Rectangle r, const char *label, Color fill, Color textColor) {
    bool hover = CheckCollisionPointRec(GetMousePosition(), r);
    DrawRectangleRounded(r, 0.2f, 8, hover ? Fade(fill, 0.85f) : fill);

    Vector2 s = MeasureTextEx(FontRegular, label, 22.0f, 1.0f);
    DrawTextEx(FontRegular, label,
               (Vector2){r.x + (r.width - s.x) / 2.0f, r.y + (r.height - s.y) / 2.0f},
               22.0f, 1.0f, textColor);
}

GameScreen gameover_update(void) {
    if (IsKeyPressed(KEY_ENTER)) return SCREEN_GAMEPLAY;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();
        if (CheckCollisionPointRec(mouse, button_rect(0))) return SCREEN_GAMEPLAY;
        if (CheckCollisionPointRec(mouse, button_rect(1))) return SCREEN_MENU;
    }
    return SCREEN_GAME_OVER;
}