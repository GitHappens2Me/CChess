#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "../header_files/move.h"


/*
void create_move(Move** move, uint64_t origin, uint64_t dest){
    *move = ( Move *)malloc(sizeof(Move));
    (*move)->origin = (int64_t *)malloc(sizeof(int64_t));
    (*move)->destination = (int64_t *)malloc(sizeof(int64_t));
    (*move)->origin = origin;
    (*move)->destination = dest;
}*/

int is_pseudo_legal_move(Board *board, Move move){
    uint64_t ps_legal_destinations = generate_pseudolegal_moves_for_piece(board, move.origin);
    return (ps_legal_destinations & move.destination > 0);
}
