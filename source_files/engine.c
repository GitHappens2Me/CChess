

#include "../header_files/engine.h"

int get_best_move(Board* board, Move* best_move, int depth, int max_depth){
    
    if(depth == max_depth){
        return evaluate(board);
    }

    Move* possible_moves = malloc(sizeof(Move) * 200);
    if (!possible_moves) {
        fprintf(stderr, "Failed to allocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }

    int num_possible_moves = generate_all_legal_moves_for_player(board, get_current_player(board), possible_moves);
        
    int best_score = (depth % 2 == 0) ? INT_MIN : INT_MAX; // Maximize on even depths, minimize on odd depths

    
    //printf("Depth %d\n", depth);
    for(int i = 0; i < num_possible_moves; i++){
        //print_move(possible_moves[i]);
    }

    Board* board_copy;
    create_board(&board_copy);

    for(int i = 0; i < num_possible_moves; i++){
        copy_board(board_copy, board);

        apply_move_forced(board_copy, possible_moves[i]);

        //printf("Depth: %d, Score: %d , Move: ", depth, evaluate(board_copy));
        //print_move(possible_moves[i]);
        //print_board(board_copy);

        int score = get_best_move(board_copy, best_move, depth + 1, max_depth);
        if (depth % 2 == 0) {
            // Maximizing player (white)
            if (score > best_score) {
                best_score = score;
                if (depth == 0) {
                    *best_move = possible_moves[i]; // Only update the best move at the root level
                }
            }
        } else {
            // Minimizing player (black)
            if (score < best_score) {
                best_score = score;
                if (depth == 0) {
                    *best_move = possible_moves[i]; // Only update the best move at the root level
                }
            }
        }
    }
    

    free(possible_moves);
    free(board_copy);
    return best_score;

}

int evaluate(Board* board){
    uint64_t temp_array[NUM_OF_BITS];
    return (split_bitmap(get_pieces_of_player(board, PLAYER_WHITE) ,temp_array) - split_bitmap(get_pieces_of_player(board, PLAYER_BLACK), temp_array));
}

