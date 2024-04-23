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
    uint64_t all_pieces = board->state[piecetype];

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
void print_board(Board* board){
    char str_board[NUM_OF_BITS + 1];
    memset(str_board, '0', NUM_OF_BITS); // Initialize the board with spaces
    str_board[NUM_OF_BITS] = '\0'; // Null terminate the string
    
    for(int piece_type = 0; piece_type < NUM_OF_PIECE_TYPES; piece_type++){
        uint64_t current_pieces = board->state[piece_type];
        for (int i = NUM_OF_BITS - 1; i >= 0; i--) {   
            if (current_pieces & ((uint64_t)1 << i)){
                str_board[NUM_OF_BITS - 1 - i] = get_symbol_for_piecetype(piece_type);
            }  
        }
    }

    for(int i = 0; i < strlen(str_board); i++){
        printf("%c", str_board[i]);
        if((i+1) % NUM_OF_COLLUMNS == 0) printf("\n");
    }
}

char get_symbol_for_piecetype(int piece_type){
    switch (piece_type) {
        case 0: return 'P';
        case 1: return 'R';
        case 2: return 'N';
        case 3: return 'B';
        case 4: return 'Q';
        case 5: return 'K';
        case 6: return 'p';
        case 7: return 'r';
        case 8: return 'n';
        case 9: return 'b';
        case 10: return 'q';
        case 11: return 'k';
        default: 
            printf("No piece-symbol for %i", piece_type);
            exit(EXIT_FAILURE);
}

}