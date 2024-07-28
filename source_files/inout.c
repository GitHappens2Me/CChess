#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../header_files/main.h"
#include "../header_files/board.h"
#include "../header_files/inout.h"



/*
 *  outputs the position of all instances of a specified piecetype to console
 *
 *  board: the board which pieces are displayed
 *  piecetype: the type of piece to be displayed (0 - 11) 
 *      See const definitions in board.h.
 * 
 *  returns: void
 */
void print_pieces(Board* board, int piecetype){

   //uint64_t all_pieces = get_all_pieces(board);
    uint64_t all_pieces = board->pieces[piecetype];

    // Determine the number of bits in an int64_t
    int numBits = sizeof(all_pieces) * 8;
    
    // Iterate through each bit from left to right
    for (int i = numBits - 1; i >= 0; i--) {
        // Check if the current bit is set
        if (all_pieces & ((uint64_t)1 << i))
            printf("1");
        else
            printf("0");

        if(i % 8 == 0){
            printf("\n");
        }
    }
    printf("\n");
}

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
void print_board(Board* board) {
    char str_board[NUM_OF_BITS + 1];
    memset(str_board, '.', NUM_OF_BITS); // Initialize the board with dots
    str_board[NUM_OF_BITS] = '\0'; // Null terminate the string

    printf("\n");
    // Place pieces on the board
    for (int piece_type = 0; piece_type < NUM_OF_PIECE_TYPES; piece_type++) {
        uint64_t current_pieces = board->pieces[piece_type];
        for (int i = NUM_OF_BITS - 1; i >= 0; i--) {
            if (current_pieces & ((uint64_t)1 << i)) {
                str_board[NUM_OF_BITS - 1 - i] = get_symbol_for_piecetype(piece_type);
            }
        }
    }
/*
    printf("   ");
    for (int col = 0; col < NUM_OF_COLLUMNS; col++) {
        printf(" %c  ", 'a' + col); // Column labels 'a' to 'h'
    }
    printf("\n");
*/

    for (int row = 0; row < NUM_OF_COLLUMNS; row++) {
        printf("%d ", NUM_OF_COLLUMNS - row); // Row labels 8 to 1
        for (int col = 0; col < NUM_OF_COLLUMNS; col++) {
            int index = row * NUM_OF_COLLUMNS + col;
            printf("| %c ", str_board[index]);
        }
        printf("|\n");
        printf("  ");
        for (int col = 0; col < NUM_OF_COLLUMNS; col++) {
            printf("+---");
        }
        printf("+\n");
    }
    printf("   ");
    for (int col = 0; col < NUM_OF_COLLUMNS; col++) {
        printf(" %c  ", 'a' + col); // Column labels 'a' to 'h'
    }
    printf("\n");

}

char get_symbol_for_piecetype(int piece_type){
    switch (piece_type) {
        case NO_PIECES: return ' ';
        case WHITE_PAWNS: return 'P';
        case WHITE_KNIGHTS: return 'N';
        case WHITE_BISHOPS: return 'B';
        case WHITE_ROOKS: return 'R';
        case WHITE_QUEENS: return 'Q';
        case WHITE_KING: return 'K';
        case BLACK_PAWNS: return 'p';
        case BLACK_KNIGHTS: return 'n';
        case BLACK_BISHOPS: return 'b';
        case BLACK_ROOKS: return 'r';
        case BLACK_QUEENS: return 'q';
        case BLACK_KING: return 'k';
        default:
            printf("No piece-symbol for %i", piece_type);
            exit(EXIT_FAILURE);
    }
}

int get_piecetype_for_symbol(char symbol){
    switch (symbol) {
        case ' ':  return NO_PIECES;
        case 'P':  return WHITE_PAWNS;
        case 'N':  return WHITE_KNIGHTS;
        case 'B':  return WHITE_BISHOPS;
        case 'R':  return WHITE_ROOKS;
        case 'Q':  return WHITE_QUEENS;
        case 'K':  return WHITE_KING;
        case 'p':  return BLACK_PAWNS;
        case 'n':  return BLACK_KNIGHTS;
        case 'b':  return BLACK_BISHOPS;
        case 'r':  return BLACK_ROOKS;
        case 'q': return BLACK_QUEENS;
        case 'k': return BLACK_KING;
        default:
            printf("No symbol for %c", symbol);
            exit(EXIT_FAILURE);
    }
}

void print_position(uint64_t position){
    // Determine the number of bits in an int64_t
    int numBits = sizeof(position) * 8;
    
    // Iterate through each bit from left to right
    for (int i = numBits - 1; i >= 0; i--) {
        // Check if the current bit is set
        if (position & ((uint64_t)1 << i))
            printf("1");
        else
            printf("0");

        if(i % 8 == 0){
            printf("\n");
        }
    }
    printf("\n");
}

Move get_move_from_user(){
    // #TODO Optimise 100 character limit 
    char* input = malloc(sizeof(char)* 100);
    char* origin = malloc(sizeof(char)* 100);
    char* destination = malloc(sizeof(char)* 100);
    if(!input || !origin || !destination){
        printf("Could not allocate Memory for User Input\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter a Move: ");
    scanf("%s", input);
    //printf("String is %d chars long.\n", strlen(input));
    
    
    
    if (strlen(input) == 4) {
        strncpy(origin, input, 2);
        origin[2] = '\0';  

        strncpy(destination, input + 2, 2);
        destination[2] = '\0';

        //printf("Origin: %s\n", origin);
        //printf("Destination: %s\n", destination);
    } else if(strlen(input) == 2){
        strncpy(origin, input, 2);
        origin[2] = '\0';
        
        printf("Enter a Destination square: ");
        scanf("%s", destination);
        //printf("Origin: %s\n", origin);
        //printf("Destination: %s\n", destination);
   
    }else{
        printf("Please enter a Move in the form of 'e2e4' or a select a piece with 'e2'\n   ");
    }

    Move user_move = create_move(get_bitmap_from_notation(origin), get_bitmap_from_notation(destination)); 

    free(origin);
    free(input);
    free(destination);

    return user_move;
    
}