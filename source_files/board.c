#include <stdlib.h>
#include <stdio.h>


#include "../header_files/main.h"
#include "../header_files/board.h"

// Allocates the necessary memory to a board
void create_board(Board** board){
    *board = ( Board *)malloc(sizeof(Board));
    (*board)->state = (int64_t *)malloc(NUM_OF_ROWS * sizeof(int64_t));
    for(int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        (*board)->state[i] = 0x0;
    }
}

// prints the given board in a human-readable form to the console 
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

// initializes board to start position
void initialize_board(Board* board){
    board->state[WHITE_PAWNS] = 0x000000000000FF00;
    board->state[WHITE_ROOKS] = 0x0000000000000081;
    board->state[WHITE_KNIGHTS] = 0x0000000000000042;
    board->state[WHITE_BISHOPS] = 0x0000000000000024;
    board->state[WHITE_QUEENS] = 0x0000000000000010;
    board->state[WHITE_KING] = 0x0000000000000008;

    board->state[BLACK_PAWNS] = 0x00FF000000000000;
    board->state[BLACK_ROOKS] = 0x8100000000000000;
    board->state[BLACK_KNIGHTS] = 0x4200000000000000;
    board->state[BLACK_BISHOPS] = 0x2400000000000000;
    board->state[BLACK_QUEENS] = 0x1000000000000000;
    board->state[BLACK_KING] = 0x0800000000000000;
}

uint64_t get_all_pieces(Board* board){
    uint64_t all_pieces = 0;
    for(int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        all_pieces = all_pieces | board->state[i];
        printf("%d\n",board->state[i]);
    }
    return all_pieces; 
}