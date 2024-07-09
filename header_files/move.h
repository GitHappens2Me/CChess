#pragma once

#include <stdlib.h>
#include <stdint.h>


// Forward Declaration of Board to prevent cyclical dependencies
// TODO: More Research on Forward Declaration
typedef struct Board Board;

// External declaration of the function to avoid cyclical dependency
extern uint64_t generate_pseudolegal_moves_for_piece(Board *board, uint64_t origin);


typedef struct {
    uint64_t origin;
    uint64_t destination;
    int piece_type;
} Move;

//void create_move(Move** move, uint64_t origin, uint64_t dest);

int is_pseudo_legal_move(Board *board, Move move);