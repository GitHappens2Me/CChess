#pragma once

#include <stdint.h>

#include "../header_files/move.h"
#include "../header_files/board.h"


//#TODO define all squares needed in code (for example castling)
#define H1 0x1
#define G1 0x2
#define F1 0x4
#define E1 0x8
#define D1 0x10
#define C1 0x20
#define B1 0x40
#define A1 0x80

#define H2 0x100
#define G2 0x200
#define F2 0x400
#define E2 0x800
#define D2 0x1000
#define C2 0x2000
#define B2 0x4000
#define A2 0x8000

#define H3 0x10000
#define G3 0x20000
#define F3 0x40000
#define E3 0x80000
#define D3 0x100000
#define C3 0x200000
#define B3 0x400000
#define A3 0x800000

#define H4 0x1000000
#define G4 0x2000000
#define F4 0x4000000
#define E4 0x8000000
#define D4 0x10000000
#define C4 0x20000000
#define B4 0x40000000
#define A4 0x80000000

#define H5 0x100000000
#define G5 0x200000000
#define F5 0x400000000
#define E5 0x800000000
#define D5 0x1000000000
#define C5 0x2000000000
#define B5 0x4000000000
#define A5 0x8000000000

#define H6 0x10000000000
#define G6 0x20000000000
#define F6 0x40000000000
#define E6 0x80000000000
#define D6 0x100000000000
#define C6 0x200000000000
#define B6 0x400000000000
#define A6 0x800000000000

#define H7 0x1000000000000
#define G7 0x2000000000000
#define F7 0x4000000000000
#define E7 0x8000000000000
#define D7 0x10000000000000
#define C7 0x20000000000000
#define B7 0x40000000000000
#define A7 0x80000000000000

#define H8 0x100000000000000
#define G8 0x200000000000000
#define F8 0x400000000000000
#define E8 0x800000000000000
#define D8 0x1000000000000000
#define C8 0x2000000000000000
#define B8 0x4000000000000000
#define A8 0x8000000000000000



#define NUM_OF_COLLUMNS (8)
#define NUM_OF_ROWS (8)
#define NUM_OF_PIECE_TYPES (13)
#define NUM_OF_BITS (64)

#define NO_PIECES (0)
#define WHITE_PAWNS (1)
#define WHITE_KNIGHTS (2)
#define WHITE_BISHOPS (3)
#define WHITE_ROOKS (4)
#define WHITE_QUEENS (5)
#define WHITE_KING (6)
#define BLACK_PAWNS (7)
#define BLACK_KNIGHTS (8)
#define BLACK_BISHOPS (9)
#define BLACK_ROOKS (10)
#define BLACK_QUEENS (11)
#define BLACK_KING (12)

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


//Castling constants

#define BLACK_QUEEN_SIDE_CASTLE_FLAG 0x8 // 1000
#define BLACK_QUEEN_SIDE_CASTLE_ATTACK_FREE_SQUARES 0x3800000000000000 // c8 & d8 & e8 
#define BLACK_KING_SIDE_CASTLE_FLAG  0x4 // 0100
#define BLACK_KING_SIDE_CASTLE_ATTACK_FREE_SQUARES 0xE00000000000000

#define WHITE_QUEEN_SIDE_CASTLE_FLAG 0x2 // 0010
#define WHITE_QUEEN_SIDE_CASTLE_ATTACK_FREE_SQUARES 0x38 // c1 & d1 & e1 
#define WHITE_KING_SIDE_CASTLE_FLAG  0x1 // 0001
#define WHITE_KING_SIDE_CASTLE_ATTACK_FREE_SQUARES 0xE // e1 & f1 & g1



// Forward declaration of Board
typedef struct Board Board;

// Define the Board struct
struct Board {
    // Defines the current state of pieces on the board
    // via 12 64Bit integers
    uint64_t* pieces;

    // TODO: Castling Rights
    uint8_t castling_rights;
    
    // Square where an en-passant capture is possible this move
    uint64_t en_passant_square;
    
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
 *  Initialized Board to empty Board
 *
 *  board: Board which gets initialized
 *
 *  returns: void
 */
void initialize_board_empty(Board* board);

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


/*
 *  returns a bitmap containing all pieces of the specified player
 *
 *  board: board, on which the pieces stand
 *  player: player, whose pieces will be returned
 *
 *  returns: 
 *          uint64_t bitmap, where a 1 signifies a piece of the given player
 *  
 *  notes: This Function gets called extremly often, therfore it is optimized more than others.
 */
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

int is_in_checkmate(Board* board, int player);

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
 */
int generate_legal_moves_for_piece(Board* board, uint64_t position, Move* legal_moves);

/*
 *  generates all pseudolegal moves (Array of type Move) for a given piece
 *  
 *  board: current board state
 *  position: position of piece
 *  legal_moves: pointer to Move-array, where the legal moves are stored
 *
 *  returns: int number of pseudolegal moves generated
 *         
 */
int generate_pseudolegal_moves_for_piece(Board* board, uint64_t position, Move* legal_moves);

int generate_pseudolegal_moves_for_pawn(Board* board, uint64_t position, int player, Move* legal_moves);
int generate_pseudolegal_moves_for_rook(Board* board, uint64_t position, int player, Move* legal_moves);
int generate_pseudolegal_moves_for_knight(Board* board, uint64_t position, int player, Move* legal_moves);
int generate_pseudolegal_moves_for_bishop(Board* board, uint64_t position, int player, Move* legal_moves);
int generate_pseudolegal_moves_for_queen(Board* board, uint64_t position, int player, Move* legal_moves);
int generate_pseudolegal_moves_for_king(Board* board, uint64_t position, int player, Move* legal_moves);

