#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "../header_files/board.h"
#include "../header_files/move.h"
#include "../header_files/inout.h"

/*
 *  Calculates the optimal Move for a given Position using the Minimax Algorithm and Alpha Beta. 
 *
 *  board: The current board-state
 *  best_move: Pointer to the best_move found
 *  max_depth: maximum number of halve-moves searched
 *
 *  returns: the score this functions gives the best move
 * 
 *  notes: 
 * 
 *  #TODO: Optomizations: e.g.  iterative deepening, killer moves, history heuristic, quiescent search
 */
int get_best_move_minimax(Board* board, Move* best_move, int max_depth);
int maxi(Board* board, int depth, int alpha, int beta);
int mini(Board* board, int depth, int alpha, int beta);

/*
 *  Evaluates the given Position without looking ahead.
 *
 *  board: The current board-state
 *
 *  returns: the score of the current position in centipawns
 *           positive scores: Advantage for White
 *           negative score:  Advantage for Black
 *            
 */
int evaluate(Board* board);

int compare_moves(const void *a, const void *b);

int calculate_material_score(Board* board);
int get_position_value(int piece_type, uint64_t position);
int get_position_value(int piece_type, uint64_t position);
int get_position_index_from_position(uint64_t position);
int get_piece_value(int piece_type);

int calculate_movement_score(Board* board);

