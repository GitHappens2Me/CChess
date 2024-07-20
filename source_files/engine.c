

#include "../header_files/engine.h"
#include <limits.h>


int get_best_move_minimax(Board* board, Move* best_move, int max_depth){
    
    printf("Starting MiniMax Calculation with Depth %d\n", max_depth);

    //#TODO #BUG remove magic number 200 -> more efficiant to just allocate the needed memory
    Move* possible_moves = malloc(sizeof(Move) * 200);
    if (!possible_moves) {
        fprintf(stderr, "Failed to allocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }

    int num_possible_moves = generate_all_legal_moves_for_player(board, get_current_player(board), possible_moves);
    if (num_possible_moves == 0) {
        free(possible_moves);
        return 0;
    }
    printf("Testing all %d rootmoves.\n",num_possible_moves);

    int best_score = (get_current_player(board) == PLAYER_WHITE) ? INT_MIN : INT_MAX;

    Board* board_copy;
    create_board(&board_copy);

    for (int i = 0; i < num_possible_moves; i++) {
        copy_board(board_copy, board);
        apply_move_forced(board_copy, possible_moves[i]);

        int current_score;
        if (get_current_player(board) == PLAYER_WHITE) {

            current_score = mini(board_copy, max_depth - 1);
            if (current_score > best_score) {
                best_score = current_score;
                *best_move = possible_moves[i];
            }
        } else {

            current_score = maxi(board_copy, max_depth - 1);
            if (current_score < best_score) {
                best_score = current_score;
                *best_move = possible_moves[i];
            }
        }
        
    }

    free_board(board_copy);
    free(possible_moves);
    return best_score;
}

int maxi(Board* board, int depth) {
    //print_board(board);
    //printf("Depth: %d",depth);
    if ( depth == 0 ) return evaluate(board);
    int max = INT_MIN;

        //#TODO remove magic number 64 -> more efficiant to just allocate the needed memory
    Move* possible_moves = malloc(sizeof(Move) * 200);
    if (!possible_moves) {
        fprintf(stderr, "Failed to allocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }

    int num_possible_moves = generate_all_legal_moves_for_player(board, get_current_player(board), possible_moves);
    //printf("%d possible Moves - ", num_possible_moves);
    if(num_possible_moves == 0){
        free(possible_moves);
        return evaluate(board);
    }
    
    Board* board_copy;
    create_board(&board_copy);
    //printf("created board - ");
    for (int i = 0; i < num_possible_moves; i++) {
        copy_board(board_copy, board);
        //printf("copied board - ");
        apply_move_forced(board_copy, possible_moves[i]);
        //printf("call recursivle\n");
        int score = mini(board_copy, depth - 1);
        if( score > max ){
            max = score;
        }
    }
    free_board(board_copy);
    free(possible_moves);
    return max;
}

int mini(Board* board, int depth) {
    //print_board(board);
    //printf("Depth: %d",depth);
    if ( depth == 0 ) return evaluate(board);
    int min = INT_MAX;

        //#TODO remove magic number 64 -> more efficiant to just allocate the needed memory
    Move* possible_moves = malloc(sizeof(Move) * 200);
    if (!possible_moves) {
        fprintf(stderr, "Failed to allocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }

    int num_possible_moves = generate_all_legal_moves_for_player(board, get_current_player(board), possible_moves);
    //printf("%d possible Moves - ", num_possible_moves);
    if(num_possible_moves == 0){
        free(possible_moves);
        return evaluate(board);
    }
    
    Board* board_copy;
    create_board(&board_copy);
    //printf("created board - ");
    for (int i = 0; i < num_possible_moves; i++) {
        copy_board(board_copy, board);
        //printf("copied board - ");
        apply_move_forced(board_copy, possible_moves[i]);
        //printf("call recursivle\n");
        int score = maxi(board_copy, depth - 1);
        if( score < min){
            min = score;
        }
    }

    free_board(board_copy);
    free(possible_moves);
    return min;
}













































int evaluate(Board* board){
    uint64_t temp_array[NUM_OF_BITS];
    return (split_bitmap(get_pieces_of_player(board, PLAYER_WHITE) ,temp_array) - split_bitmap(get_pieces_of_player(board, PLAYER_BLACK), temp_array));
}

