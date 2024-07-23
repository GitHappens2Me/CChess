#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "../header_files/board.h"
#include "../header_files/move.h"
#include "../header_files/inout.h"

int get_best_move_minimax(Board* board, Move* best_move, int max_depth);
int maxi(Board* board, int depth, int alpha, int beta);
int mini(Board* board, int depth, int alpha, int beta);

int evaluate(Board* board);

int calculate_material_score(Board* board);
int get_position_value(int piece_type, uint64_t position);
int get_position_value(int piece_type, uint64_t position);
int get_position_index_from_position(uint64_t position);
int get_piece_value(int piece_type);

int calculate_movement_score(Board* board);

