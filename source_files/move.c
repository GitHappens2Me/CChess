#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "../header_files/move.h"

Move create_move(uint64_t origin, uint64_t destination) {
    Move move;
    move.origin = origin;
    move.destination = destination;
    return move;
}


int is_legal_move(Board *board, Move move){
    return (is_pseudo_legal_move(board, move) && !results_in_check(board, move));
}

int is_pseudo_legal_move(Board *board, Move move){

    // Check if it is that Players turn:
    if (get_piece_color(board, move.origin) != get_current_player(board)){
        printf("Not your turn\n");
        return 0;
    }

    uint64_t ps_legal_destinations = generate_pseudolegal_moves_for_piece(board, move.origin);
    //print_position(ps_legal_destinations);
    //print_position(move.destination);
    return (ps_legal_destinations & move.destination) > 0;
}

void print_move(Move move){
    char* origin = get_notation_from_bitmap(move.origin);
    char* destination = get_notation_from_bitmap(move.destination);
    
    printf("%s -> %s\n", origin, destination);

    free(origin);
    free(destination);
}

int get_moves_from_destination_bitmap(uint64_t piece_position, uint64_t legal_destinations, Move* legal_moves_by_piece){
   
    int number_of_bits = 64; // NUM_OF_BITS is not reachable from move.c (maybe move it to main.h?) 
    int counter = 0;
    uint64_t current_destination = 1ULL;

    //Move test_move = {0x100, 0x10000};

    for (int i = 0; i < number_of_bits; i++) {
        // Check if the current bit is set
        if (legal_destinations & current_destination){
            Move new_move;
            new_move.origin = piece_position;
            new_move.destination = current_destination;

            // Assign the new Move object to the array
            legal_moves_by_piece[counter] = new_move;

            // Increment the counter
            
            counter++;
            if(counter >= 28) printf("Allocated memory not sufficiant: Counter %d\n", counter);
        }
        current_destination <<= 1;
    }
    return counter;

}