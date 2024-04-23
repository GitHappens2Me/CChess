#pragma once

#include <stdint.h>
#include "../header_files/move.h"


#define NUM_OF_COLLUMNS (8)
#define NUM_OF_ROWS (8)
#define NUM_OF_PIECE_TYPES (12)
#define NUM_OF_BITS (64)

#define WHITE_PAWNS 0
#define WHITE_ROOKS 1
#define WHITE_KNIGHTS 2
#define WHITE_BISHOPS 3
#define WHITE_QUEENS 4
#define WHITE_KING 5
#define BLACK_PAWNS 6
#define BLACK_ROOKS 7
#define BLACK_KNIGHTS 8
#define BLACK_BISHOPS 9
#define BLACK_QUEENS 10
#define BLACK_KING 11



typedef struct {
    // defines the current State of pieces on the board
    // via 12 64Bit integers
    uint64_t* pieces;
    // TODO: Castling Rights
    // TODO: en Passant
} Board;


void create_board(Board** board);


// initializes board to start position
void initialize_board(Board* board);

// returns integer that represents the position of all pieces (white and black)
uint64_t get_all_pieces(Board* board);

int apply_move(Board* board, Move move);
