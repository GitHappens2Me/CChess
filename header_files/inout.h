#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "../header_files/main.h"
#include "../header_files/board.h"



/*
 *  outputs the position of all instances of a specified piecetype to console
 *
 *  board: the board which pieces are displayed
 *  piecetype: the type of piece to be displayed (0 - 11) 
 *      See const definitions in board.h.
 * 
 *  returns: void
 */
void print_pieces(Board* board, int piecetype);

/*
 *  outputs the position of all pieces to console
 *  using the get_symbol_for_piecetype function to translate from piece_type to symbol
 *  e.g.  0 (WHITE_PAWNS) -> P  
 *        6 (BLACK_PAWNS) -> p 
 * 
 *  board: the board which pieces are displayed
 * 
 *  returns: void
 */
void print_board(Board* board);

char get_symbol_for_piecetype(int piece_type);
int get_piecetype_for_symbol(char symbol);

void print_position(uint64_t position);

Move get_move_from_user(Board* board);