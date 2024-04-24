#pragma once

#include <stdlib.h>
#include <stdint.h>


typedef struct {
    uint64_t origin;
    uint64_t destination;
    int piece_type;
} Move;

//int is_move_valid(Board* board, Move move);


// returns bitmap of possible "movement vector". 
// -> all squares a rook at given position can move to on an empty board 
uint64_t rook_move_vector(uint64_t position);
