#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "../header_files/move.h"
#include "../header_files/board.h"


uint64_t rook_move_vector(uint64_t position) {
    uint64_t moves = 0ULL;

    // Calculate possible horizontal moves
    uint64_t horizontal_moves = position;
    for (int i = 0; i < NUM_OF_COLLUMNS; ++i) {
        horizontal_moves |= (horizontal_moves << 1) & 0xFEFEFEFEFEFEFEFEULL; // Shift left by one, masking the rightmost column
        horizontal_moves |= (horizontal_moves >> 1) & 0x7F7F7F7F7F7F7F7FULL; // Shift right by one, masking the leftmost column
    }
    moves |= horizontal_moves;

    // Calculate possible vertical moves
    uint64_t vertical_moves = position;
    for (int i = 0; i < NUM_OF_ROWS; ++i) {
        vertical_moves |= (vertical_moves << 8) & 0xFFFFFFFFFFFFFF00ULL; // Shift up by 8, masking the bottom row
        vertical_moves |= (vertical_moves >> 8) & 0x00FFFFFFFFFFFFFFULL; // Shift down by 8, masking the top row
    }
    moves |= vertical_moves;

    // Remove the current position from the moves
    moves &= ~position;

    return moves;
}