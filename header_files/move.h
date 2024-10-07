#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "../header_files/notation.h"


// Forward Declaration of Board to prevent cyclical dependencies
// TODO: More Research on Forward Declaration
typedef struct Board Board;

typedef struct {

    // Quit Moves
    int moving_piece_type;
    uint64_t moving_piece_origin;
    uint64_t moving_piece_destination;

    // Captures
    int captured_piece_type;
    uint64_t captured_piece_position;

    // Castling
    uint64_t castling_rook_position;

    // Pawn-Promotion
    int promotion_to_type;

    // Square which is skipped by a pawn doing a double move
    // e.g. Square where a en-passant is possible next move
    uint64_t en_passant_square;

} Move;

// External declaration of the function to avoid cyclical dependency
extern int generate_pseudolegal_moves_for_piece(Board* board, uint64_t position, Move* legal_moves);
extern void print_position(uint64_t position);
extern int get_piece_color(Board *board, uint64_t position);
extern int get_current_player(Board *board); // this is needed for checking whose turn it is but it is convoluted
extern int results_in_check(Board* board, Move move);

void create_move(Move* move, int moving_piece_type, uint64_t moving_piece_origin, uint64_t moving_piece_destination, 
                 int captured_piece_type, uint64_t captured_piece_position, 
                 uint64_t castling_rook_position, int promotion_to_type, uint64_t en_passant_square);

void print_move(Move move);

int get_moves_from_destination_bitmap(uint64_t piece_position, uint64_t legal_destinations, Move* legal_moves_by_piece);

int is_legal_move(Board *board, Move move);

int is_pseudo_legal_move(Board *board, Move move);