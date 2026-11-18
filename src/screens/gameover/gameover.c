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

static void draw_button(Rectangle r, const char *label) {
    bool hover = CheckCollisionPointRec(GetMousePosition(), r);
    DrawRectangleRec(r, hover ? LIGHTGRAY : GRAY);

    Vector2 s = MeasureTextEx(FontRegular, label, 26.0f, 1.0f);
    DrawTextEx(FontRegular, label,
               (Vector2){r.x + (r.width - s.x) / 2.0f, r.y + (r.height - s.y) / 2.0f},
               26.0f, 1.0f, WHITE);
}

GameScreen gameover_update(void) {
    Vector2 mouse = GetMousePosition();
    bool clicou = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if ((clicou && CheckCollisionPointRec(mouse, button_rect(0))) || IsKeyPressed(KEY_R)) {
        return SCREEN_GAMEPLAY;   // o main.c chama game_init e toca a música
    }
    if (clicou && CheckCollisionPointRec(mouse, button_rect(1))) {
        return SCREEN_MENU;
    }
    return SCREEN_GAME_OVER;
}

void gameover_draw(const Game *game, const ScoreList *scores) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));

    float h = (float)GetScreenHeight();

    Vector2 t = MeasureTextEx(FontTitle, "GAME OVER", 80.0f, 1.0f);
    DrawTextEx(FontTitle, "GAME OVER",
               (Vector2){((float)GetScreenWidth() - t.x) / 2.0f, h * 0.12f},
               80.0f, 1.0f, RED);

    draw_centered(TextFormat("Pontos: %d", game->score), 36.0f, h * 0.30f, WHITE);
    draw_centered(TextFormat("Melhor: %d", scores_best(scores)), 28.0f, h * 0.30f + 50.0f, YELLOW);

    draw_button(button_rect(0), "JOGAR NOVAMENTE");
    draw_button(button_rect(1), "MENU");
}