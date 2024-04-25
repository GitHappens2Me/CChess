#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "../header_files/main.h"
#include "../header_files/board.h"
#include "../header_files/move.h"

// Allocates the necessary memory to a board
void create_board(Board** board){
    printf("Creating Board\n");
    *board = ( Board *)malloc(sizeof(Board));
    (*board)->pieces = (int64_t *)malloc(NUM_OF_ROWS * sizeof(int64_t));
    for(int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        (*board)->pieces[i] = 0x0;
    }
}



// initializes board to start position
void initialize_board(Board* board){
    printf("Initializing Board\n");
    board->pieces[WHITE_PAWNS] = 0x000000000000FF00;
    board->pieces[WHITE_ROOKS] = 0x0000000000000081;
    board->pieces[WHITE_KNIGHTS] = 0x0000000000000042;
    board->pieces[WHITE_BISHOPS] = 0x0000000000000024;
    board->pieces[WHITE_QUEENS] = 0x0000000000000010;
    board->pieces[WHITE_KING] = 0x0000000000000008;

    board->pieces[BLACK_PAWNS] = 0x00FF000000000000;
    board->pieces[BLACK_ROOKS] = 0x8100000000000000;
    board->pieces[BLACK_KNIGHTS] = 0x4200000000000000;
    board->pieces[BLACK_BISHOPS] = 0x2400000000000000;
    board->pieces[BLACK_QUEENS] = 0x1000000000000000;
    board->pieces[BLACK_KING] = 0x0800000000000000;
}

uint64_t get_all_pieces(Board* board){
    uint64_t all_pieces = 0;
    for(int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        all_pieces = all_pieces | board->pieces[i];
        printf("%d\n",board->pieces[i]);
    }
    return all_pieces; 
}


int apply_move(Board* board, Move move){
    // is_VALID Check
    if (1){
        //remove piece from origin
        board->pieces[move.piece_type] = board->pieces[move.piece_type] & ~move.origin;
        //add piece to destination
        board->pieces[move.piece_type] = board->pieces[move.piece_type] | move.destination;
        //TODO Capture etc.
    }
}


uint64_t get_pieces_of_player(Board* board, int player){
    uint64_t all_pieces = 0;
    if(player == PLAYER_WHITE){
        for(int i = 0; i < 6; i++){
            all_pieces = all_pieces | board->pieces[i];
        }
    }else if(player == PLAYER_BLACK){
        for(int i = 6; i < 12; i++){
            all_pieces = all_pieces | board->pieces[i];
        }
    }
    return all_pieces; 
}
