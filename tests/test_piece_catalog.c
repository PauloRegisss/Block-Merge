#include "materials/piece.h"

#include <assert.h>
#include <stddef.h>

int main(void) {
    for (int i = 0; i < PIECE_SHAPE_COUNT; i++) {
        Piece piece;
        assert(piece_create_from_shape(i, &piece));
        assert(piece_count_block(&piece) > 0);
    }

    Piece piece;
    assert(!piece_create_from_shape(-1, &piece));
    assert(!piece_create_from_shape(PIECE_SHAPE_COUNT, &piece));
    assert(!piece_create_from_shape(0, NULL));
    return 0;
}
