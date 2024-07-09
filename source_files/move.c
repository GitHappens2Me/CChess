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
    printf("%s -> %s\n", get_notation_from_bitmap(move.origin), get_notation_from_bitmap(move.destination));
}