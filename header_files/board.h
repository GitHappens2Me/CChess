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

/*----------------------------------------
                Board creation 
                & Initialzation
------------------------------------------*/

/*
 *  allocates Memory for the board Pointer
 *
 *  board: the board, which the allocated memory belongs to
 *
 *  returns: void
 * 
 *  notes: 
 *          The Pieces get initialized to 0x0UUL (Empty Board)
 *          The First Player to move is PLAYER_WHITE (0)
 */
void create_board(Board** board);

/*
 *  frees the Memory of a board
 *
 *  board: the board, which memory is freed
 *
 *  returns: void
 * 
 *  notes: 
 */
void free_board(Board* board);

/*
 *  creates a deep copy of a board 
 *
 *  copy: Board-Pointer holding the copy
 *  source: Board, which gets copied
 *
 *  returns: void
 * 
 *  notes:  copy_board does not allocate memory for the copy
 *          create_board has to be called first
 */
void copy_board(Board* copy, Board* source);

/*
 *  Initialized Board to Starting Position
 *
 *  board: Board which gets initialized
 *
 *  returns: void
 */
void initialize_board(Board* board);

/*
 *  Initalizes Board to a position given by FEN String
 *
 *  board: Board which gets initialized
 *  fen_string: FEN-position
 *
 *  returns: void
 * 
 *  notes: 
 * 
 *  #TODO: ATM only the pieces and the active player gets initialized
 */

void initialize_board_FEN(Board* board, char* fen_string);



/*----------------------------------------
                        ???
                This Function might
                fit better elsewhere
------------------------------------------*/


/*
 *  splits the a bitmap into an array of bitmaps with only one bit set
 *
 *  pieces: uint64_t bitmap of all pieces 
 *  indivdual_pieces: pointer to array of uint64_t bitmaps with one bit set
 *
 *  returns: number of pieces 
 */ 
int split_bitmap(uint64_t pieces, uint64_t* indivdual_pieces);





/*----------------------------------------
                Apply Moves
------------------------------------------*/

/*
 *  changes the boardstate according to the provided move if the move is valid
 *
 *  board: board on which the move is made
 *  move: move which is made
 *  
 *  returns: 
 *          1: if move was applied
 *          0: if move couldnt be applied (invalid move)
 *  
 *  notes: Applying the move is done via the apply_move_forced function after validity test
 * 
 */ 
int apply_move(Board* board, Move move);

/*
 *  changes the boardstate according to the provided move without any checks
 *
 *  board: board on which the move is made
 *  move: move which is made
 *  
 *  returns: void
 *  
 *  notes: 
 * 
 */ 
void apply_move_forced(Board* board, Move move);


/*----------------------------------------
                Board Information
------------------------------------------*/

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




/*----------------------------------------
                Checks
------------------------------------------*/

int is_in_check(Board* board, int king_color);

int results_in_check(Board* board, Move move);

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



/*----------------------------------------
                Move Generation
------------------------------------------*/

/*
 *  generates all legal moves (Array of type Move) for the specified player at the current boardstate
 *  
 *  board, current board state
 *  player: player, whose moves are generated
 *  legal_moves: pointer to Move-array, where the legal moves are stored
 *
 *  returns: number of legal_moves for that player
 * 
 *  notes: 
 */
int generate_all_legal_moves_for_player(Board* board, int player, Move* legal_moves);

/*
 *  generates all legal moves (Array of type Move) for a given piece
 *  
 *  board, current board state
 *  position: position of piece
 *  legal_moves: pointer to Move-array, where the legal moves are stored
 *
 *  returns: number of legal_moves for that piece
 * 
 *  notes: This is the function where the Transition between Moves as a uint64 Bitmap to an array of Move-objects occur
 *         
 */
int generate_legal_moves_for_piece(Board* board, uint64_t position, Move* legal_moves);

/*
 *  generates all pseudolegal moves (Array of type Move) for a given piece
 *  
 *  board: current board state
 *  position: position of piece
 *  legal_moves: pointer to Move-array, where the legal moves are stored
 *
 *  returns: uint64 bitmap of pseudolegal destinations
 *         
 */
uint64_t generate_pseudolegal_moves_for_piece(Board* board, uint64_t position);

uint64_t generate_pseudolegal_moves_for_pawn(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_rook(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_knight(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_bishop(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_queen(Board* board, uint64_t position, int player);
uint64_t generate_pseudolegal_moves_for_king(Board* board, uint64_t position, int player);

