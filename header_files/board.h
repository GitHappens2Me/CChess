#pragma once

#include <stdint.h>
#include "../header_files/move.h"
#include "../header_files/board.h"


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

#define PLAYER_WHITE 0
#define PLAYER_BLACK 1

#define LEFT 0
#define RIGHT 1


//TODO rename COLLUMN to RANK
#define ROW_1 0xFF
#define COLLUMN_a 0x8080808080808080
#define ROW_8 0xFF00000000000000
#define COLLUMN_h 0x1010101010101


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

uint64_t get_pieces_of_player(Board* board, int player);

uint64_t generate_all_legal_moves(Board board, int player);
uint64_t generate_all_peseudolegal_moves(Board board, int player);

uint64_t generate_pseudolegal_moves_for_piece(Board* board, uint64_t position);
uint64_t generate_pseudolegal_moves_for_pawn(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_rook(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_knight(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_bishop(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_queen(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_king(Board* board, uint64_t position, int player);

int get_piece_type_at(Board* board, uint64_t position);
int get_opponent(int player);