#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "../header_files/notation.h"



// Forward Declaration of Board to prevent cyclical dependencies
// TODO: More Research on Forward Declaration
typedef struct Board Board;

// External declaration of the function to avoid cyclical dependency
extern uint64_t generate_pseudolegal_moves_for_piece(Board *board, uint64_t origin);
extern void print_position(uint64_t position);
extern int get_piece_color(Board *board, uint64_t position);
extern int get_current_player(Board *board); // this is needed for checking whose turn it is but it is convoluted



typedef struct {
    uint64_t origin;
    uint64_t destination;
} Move;


Move create_move(uint64_t origin, uint64_t destination);

void print_move(Move move);

int is_pseudo_legal_move(Board *board, Move move);