#pragma once

#include <stdlib.h>
#include <stdint.h>


typedef struct {
    uint64_t origin;
    uint64_t destination;
    int piece_type;
} Move;

//int is_move_valid(Board* board, Move move);
