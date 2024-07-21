#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "../header_files/board.h"
#include "../header_files/move.h"
#include "../header_files/inout.h"

float get_best_move_minimax(Board* board, Move* best_move, int max_depth);
float maxi(Board* board, int depth);
float mini(Board* board, int depth);

float evaluate(Board* board);

float calculate_material_score(Board* board);
float get_piece_value(int piece_type);

float calculate_movement_score(Board* board);

