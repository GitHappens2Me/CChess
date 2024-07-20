#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "../header_files/board.h"
#include "../header_files/move.h"
#include "../header_files/inout.h"

int get_best_move(Board* board, Move* best_move, int depth, int max_depth);

int evaluate(Board* board);

int get_best_move_minimax(Board* board, Move* best_move, int max_depth);
int negaMax(Board* board, int depth);


int maxi(Board* board, int depth);
    
int mini(Board* board, int depth);

