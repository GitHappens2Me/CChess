#pragma once

#include <stdint.h>

#include "../header_files/move.h"
#include "../header_files/board.h"



#define NUM_OF_COLLUMNS (8)
#define NUM_OF_ROWS (8)
#define NUM_OF_PIECE_TYPES (12)
#define NUM_OF_BITS (64)

#define WHITE_PAWNS (0)
#define WHITE_ROOKS (1)
#define WHITE_KNIGHTS (2)
#define WHITE_BISHOPS (3)
#define WHITE_QUEENS (4)
#define WHITE_KING (5)
#define BLACK_PAWNS (6)
#define BLACK_ROOKS (7)
#define BLACK_KNIGHTS (8)
#define BLACK_BISHOPS (9)
#define BLACK_QUEENS (10)
#define BLACK_KING (11)

#define PLAYER_WHITE (0)
#define PLAYER_BLACK (1)

#define LEFT (0)
#define RIGHT (1)

#define FORCED (0)
#define UNFORCED (1)


//TODO rename ROW to RANK & COllumn to FIle
#define ROW_1 0xFF
#define COLLUMN_a 0x8080808080808080
#define ROW_8 0xFF00000000000000
#define COLLUMN_h 0x101010101010101

#define ROW_2 0x000000000000FF00
#define ROW_7 0x00FF000000000000
#define COLLUMN_b 0x4040404040404040
#define COLLUMN_g 0x202020202020202

// Forward declaration of Board
typedef struct Board Board;

// Define the Board struct
struct Board {
    // Defines the current state of pieces on the board
    // via 12 64Bit integers
    uint64_t* pieces;
    // TODO: Castling Rights
    // TODO: en Passant
    
    // Defines whose turn is is
    int current_Player;
};


void create_board(Board** board);

// initializes board to start position
void initialize_board(Board* board);

void initialize_board_FEN(Board* board, char* fen_string);

/*
 *  splits the a bitmap into an array of bitmaps with only one bit set
 *
 *  pieces: uint64_t bitmap of all pieces 
 *  indivdual_pieces: pointer to array of uint64_t bitmaps with one bit set
 *
 *  returns: number of pieces 
 */ 
int split_bitmap(uint64_t pieces, uint64_t* indivdual_pieces);

/*
Applies move to board. Checks for validity of move first, except forced = True
*/
int apply_move(Board* board, Move move, int forced);

// returns integer that represents the position of all pieces (white and black)
uint64_t get_all_pieces(Board* board);
uint64_t get_pieces_of_player(Board* board, int player);
uint64_t get_all_pieces_of_type(Board* board, int piece_type);

/*
 *  returns the piece_type of piece at the specified square
 *
 *  board: board which is tested
 *  position: square, where the piece is standing
 *
 *  returns: 
 *          the piece_type acording to this list:
 *          Empty Squares = -1
 *          WHITE_PAWNS =    0
 *          WHITE_ROOKS =    1
 *          WHITE_KNIGHTS =  2
 *          WHITE_BISHOPS =  3
 *          WHITE_QUEENS =   4
 *          WHITE_KING =     5
 *          BLACK_PAWNS =    6
 *          BLACK_ROOKS =    7
 *          BLACK_KNIGHTS =  8
 *          BLACK_BISHOPS =  9
 *          BLACK_QUEENS =  10
 *          BLACK_KING =    11
 *  
 *  notes: Empty squares return -1, which might cause a #BUG (see get_piece_color())
 */ 
int get_piece_type_at(Board* board, uint64_t position);

/*
 *  returns the player to which the piece on the specified square belongs to  
 *
 *  board: board which is tested
 *  position: square, the piece stands on
 *  
 *  returns: 
 *          PLAYER_WHITE ( 0 ) or PLAYER_BLACK ( 1 )
 *          depending on whose piece it is
 *  
 *  notes: 
 * 
 *  #BUG: Empty squares belong to White as the check (piece_type <= 5) is true for -1
 *        which is what get_piece_type_at() returnes for empty squares. 
 */ 
int get_piece_color(Board *board, uint64_t position);

/*
 *  returns the current player 
 *
 *  board: board from which the current player is retuned
 *
 *  returns: 
 *          PLAYER_WHITE ( 0 ) or PLAYER_BLACK ( 1 )
 *          depending on whose turn it is
 *  
 *  notes: this function is funcionally identical with: board->current_Player;
 */ 
int get_current_player(Board *board);

/*
 *  returns the opponent of the specified player
 *
 *  player: player, whose opponent will be returned
 *
 *  returns: 
 *          PLAYER_WHITE ( 0 ), if player == PLAYER_BLACK ( 1 )
 *          PLAYER_BLACK ( 1 ), if player == PLAYER_WHITE ( 0 )
 */ 
int get_opponent(int player);

/*
 *  tests if a specified square is attacked by the specified player
 *  
 *  b: board, on which is being tested
 *  position: square, which is tested
 *  attacking_color: color of the (potentially) attacking player
 *
 *  returns: 
 *           1, if square is attacked
 *           0, if square is not attacked
 * 
 *  notes: 
 */
int is_attacked(Board* board, uint64_t position, int attacking_color);


/*
 *  generates all legal moves for the specified player at the current boardstate
 *  
 *  b: board, current board state
 *  player: player, whose moves are generated
 *
 *  returns: 
 *           array of type Move
 * 
 *  notes: This Function returns an array of type "Move". In contrast to returning a uint64_t bitmap of all legal destination squares
 *         #TODO a "count_legal_moves" function might be needed to initialize a sufficiant array beforehand
 */
Move* generate_all_legal_moves_for_player(Board* board, int player);
//uint64_t generate_all_peseudolegal_moves(Board board, int player);

uint64_t generate_pseudolegal_moves_for_piece(Board* board, uint64_t position);

uint64_t generate_pseudolegal_moves_for_pawn(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_rook(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_knight(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_bishop(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_queen(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_king(Board* board, uint64_t position, int player);

