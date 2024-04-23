#pragma once

#include <stdlib.h>
#include <stdint.h>

#define NUM_OF_COLLUMNS (8)
#define NUM_OF_ROWS (8)
#define NUM_OF_PIECE_TYPES (12)



typedef struct {
    // defines the current State of pieces on the board
    uint64_t* state;
    // TODO: Castling Rights
    // TODO: en Passant
} Board;


void create_board(Board** board);

// prints the given board in a human-readable form to the console 
void print_board(Board* board);

// initializes board to start position
void initialize_board(Board* board);

// returns integer that represents the position of all pieces (white and black)
uint64_t get_all_pieces(Board* board);
