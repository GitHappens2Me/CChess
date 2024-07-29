#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "../header_files/move.h"

Move create_move(int moving_piece_type, uint64_t moving_piece_origin, uint64_t moving_piece_destination, 
                 int captured_piece_type, uint64_t captured_piece_position, 
                 uint64_t castling_rook_position, int promotion_to_type, uint64_t en_passant_square) {
    Move move;

    // Quit Moves
    move.moving_piece_type = moving_piece_type;
    move.moving_piece_origin = moving_piece_origin;
    move.moving_piece_destination = moving_piece_destination;

    // Captures
    move.captured_piece_type = captured_piece_type;
    move.captured_piece_position = captured_piece_position;

    // Castling
    move.castling_rook_position = castling_rook_position;

    // Pawn-Promotion
    move.promotion_to_type = promotion_to_type; 

    move.en_passant_square = en_passant_square;

    return move;
}


int is_legal_move(Board *board, Move move){
    return (is_pseudo_legal_move(board, move) && !results_in_check(board, move));
}

int is_pseudo_legal_move(Board *board, Move move){


    Move* pseudo_legal_moves = malloc(sizeof(uint64_t) * 200);
    int move_counter = generate_pseudolegal_moves_for_piece(board, move.moving_piece_origin, pseudo_legal_moves);
    for(int i = 0; i < move_counter; i++){
        if(move.moving_piece_origin == pseudo_legal_moves[i].moving_piece_origin && 
           move.moving_piece_destination == pseudo_legal_moves[i].moving_piece_destination){
                free(pseudo_legal_moves);
                return 1;
        }
    }
    free(pseudo_legal_moves);
    return 0;

}

void print_move(Move move){
    char* origin = get_notation_from_bitmap(move.moving_piece_origin);
    char* destination = get_notation_from_bitmap(move.moving_piece_destination);
    
    printf("%s -> %s\n", origin, destination);

    free(origin);
    free(destination);
}

/*
int get_moves_from_destination_bitmap(uint64_t piece_position, uint64_t legal_destinations, Move* legal_moves_by_piece){
   
    int number_of_bits = 64; // NUM_OF_BITS is not reachable from move.c (maybe move it to main.h?) 
    int counter = 0;
    uint64_t current_destination = 1ULL;

    //Move test_move = {0x100, 0x10000};

    for (int i = 0; i < number_of_bits; i++) {
        // Check if the current bit is set
        if (legal_destinations & current_destination){
            
            legal_moves_by_piece[counter] = create_move(piece_position, current_destination);
            // Increment the counter
            
            counter++;
        }
        current_destination <<= 1;
    }
    return counter;

}
*/