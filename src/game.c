#include <math.h>
#include "game.h"
#include "fonts.h"

#define CELL_SIZE 60        // tamanho da célula no tabuleiro
#define GAP 4               // espaço entre células
#define TRAY_CELL 36        // células menores na bandeja
#define BOARD_ORIGIN_Y 40
#define SLOT_SIZE (PIECE_SIZE * TRAY_CELL + (PIECE_SIZE - 1) * GAP)
#define SLOT_SPACING 40

// ---------- layout ----------

static int board_origin_x(void) {
    int larguraGrade = BOARD_SIZE * CELL_SIZE + (BOARD_SIZE - 1) * GAP;
    return (GetScreenWidth() - larguraGrade) / 2;
}

// retângulo do slot i da bandeja (abaixo do tabuleiro, centralizado)
static Rectangle tray_slot(int i) {
    int larguraGrade = BOARD_SIZE * CELL_SIZE + (BOARD_SIZE - 1) * GAP;
    int total = TRAY_SIZE * SLOT_SIZE + (TRAY_SIZE - 1) * SLOT_SPACING;
    float startX = (GetScreenWidth() - total) / 2.0f;
    float y = BOARD_ORIGIN_Y + larguraGrade + 40;
    return (Rectangle){startX + i * (SLOT_SIZE + SLOT_SPACING), y, SLOT_SIZE, SLOT_SIZE};
}

// ---------- lógica ----------

static void refill_tray(Game *game) {
    for (int i = 0; i < TRAY_SIZE; i++) {
        game->tray[i] = piece_create_random();
        game->used[i] = false;
    }
}

// canto superior esquerdo da peça, em pixels, com a peça centralizada no mouse
static Vector2 drag_top_left(const Piece *piece, Vector2 mouse) {
    float w = piece_width(piece) * (CELL_SIZE + GAP) - GAP;
    float h = piece_height(piece) * (CELL_SIZE + GAP) - GAP;
    return (Vector2){mouse.x - w / 2.0f, mouse.y - h / 2.0f};
}

// converte a posição do mouse em linha/coluna do tabuleiro
// é a conta inversa do board_draw: x = origem + coluna * (CELL_SIZE + GAP)
static void mouse_to_cell(const Piece *piece, Vector2 mouse, int *row, int *col) {
    Vector2 tl = drag_top_left(piece, mouse);
    float step = CELL_SIZE + GAP;
    // floorf + 0.5 arredonda para a célula mais próxima (funciona com negativos)
    *col = (int)floorf((tl.x - board_origin_x()) / step + 0.5f);
    *row = (int)floorf((tl.y - BOARD_ORIGIN_Y) / step + 0.5f);
}

// true se pelo menos uma peça ainda não usada cabe em algum lugar
static bool has_any_move(const Game *game) {
    for (int i = 0; i < TRAY_SIZE; i++) {
        if (!game->used[i] && board_can_place_anywhere(&game->board, &game->tray[i])) {
            return true;
        }
    }
    return false;
}

void game_init(Game *game) {
    board_init(&game->board);
    game->score = 0;
    game->dragging = -1;
    refill_tray(game);
}

GameScreen game_update(Game *game) {
    Vector2 mouse = GetMousePosition();

    // 1) começou a arrastar: clique dentro de um slot com peça disponível
    if (game->dragging == -1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for (int i = 0; i < TRAY_SIZE; i++) {
            if (!game->used[i] && CheckCollisionPointRec(mouse, tray_slot(i))) {
                game->dragging = i;
                break;
            }
        }
    }

    // 2) soltou o botão: tenta colocar a peça
    if (game->dragging != -1 && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        int idx = game->dragging;
        const Piece *piece = &game->tray[idx];
        int row, col;
        mouse_to_cell(piece, mouse, &row, &col);

        if (board_can_place(&game->board, piece, row, col)) {
            board_place(&game->board, piece, row, col);
            game->score += piece_count_block(piece);
            int linhas = board_clear_lines(&game->board);
            game->score += linhas * 10;
            game->used[idx] = true;

            // usou as 3: repõe a bandeja
            bool todasUsadas = true;
            for (int i = 0; i < TRAY_SIZE; i++) {
                if (!game->used[i]) todasUsadas = false;
            }
            if (todasUsadas) refill_tray(game);

            game->dragging = -1;
            if (!has_any_move(game)) return SCREEN_GAME_OVER;
        }
        // se não coube, a peça simplesmente volta para o slot
        game->dragging = -1;
    }

    return SCREEN_GAMEPLAY;
}

// ---------- desenho ----------

void game_draw(const Game *game) {
    Vector2 mouse = GetMousePosition();
    int originX = board_origin_x();

    board_draw(&game->board, originX, BOARD_ORIGIN_Y, CELL_SIZE, GAP);

    // pontuação
    DrawTextEx(FontRegular, TextFormat("PONTOS: %d", game->score),
               (Vector2){40.0f, 40.0f}, 32.0f, 1.5f, RAYWHITE);

    // bandeja
    for (int i = 0; i < TRAY_SIZE; i++) {
        Rectangle slot = tray_slot(i);
        DrawRectangleRounded(slot, 0.1f, 4, (Color){30, 40, 66, 255});

        if (game->used[i] || game->dragging == i) continue;

        const Piece *p = &game->tray[i];
        int pw = piece_width(p) * (TRAY_CELL + GAP) - GAP;
        int ph = piece_height(p) * (TRAY_CELL + GAP) - GAP;
        int x = (int)(slot.x + (slot.width - pw) / 2);
        int y = (int)(slot.y + (slot.height - ph) / 2);
        piece_draw(p, x, y, TRAY_CELL, GAP);
    }

    // peça sendo arrastada + prévia de onde ela vai cair
    if (game->dragging != -1) {
        const Piece *p = &game->tray[game->dragging];
        int row, col;
        mouse_to_cell(p, mouse, &row, &col);

        if (board_can_place(&game->board, p, row, col)) {
            Color cor = Fade(piece_get_color(p), 0.4f);
            for (int i = 0; i < PIECE_SIZE; i++) {
                for (int j = 0; j < PIECE_SIZE; j++) {
                    if (p->shape[i][j] == 1) {
                        DrawRectangle(originX + (col + j) * (CELL_SIZE + GAP),
                                      BOARD_ORIGIN_Y + (row + i) * (CELL_SIZE + GAP),
                                      CELL_SIZE, CELL_SIZE, cor);
                    }
                }
            }
        }

        Vector2 tl = drag_top_left(p, mouse);
        piece_draw(p, (int)tl.x, (int)tl.y, CELL_SIZE, GAP);
    }
}