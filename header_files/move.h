#pragma once

#include <stdlib.h>
#include <stdint.h>



typedef struct {
    uint64_t origin;
    uint64_t destination;
    int piece_type;
} Move;

//void create_move(Move** move, uint64_t origin, uint64_t dest);

//int is_pseudo_legal_move(Board *board, Move move);