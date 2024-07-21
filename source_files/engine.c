

#include "../header_files/engine.h"
#include <limits.h>
#include <float.h>


float get_best_move_minimax(Board* board, Move* best_move, int max_depth){
    
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

    float best_score = (get_current_player(board) == PLAYER_WHITE) ? -FLT_MAX : FLT_MAX;

    Board* board_copy;
    create_board(&board_copy);

    for (int i = 0; i < num_possible_moves; i++) {
        copy_board(board_copy, board);
        apply_move_forced(board_copy, possible_moves[i]);

        float current_score;
        if (get_current_player(board) == PLAYER_WHITE) {

            current_score = mini(board_copy, max_depth - 1, -FLT_MAX, FLT_MAX);
            if (current_score > best_score) {
                best_score = current_score;
                *best_move = possible_moves[i];
            }
        } else {

            current_score = maxi(board_copy, max_depth - 1, -FLT_MAX, FLT_MAX);
            if (current_score < best_score) {
                best_score = current_score;
                *best_move = possible_moves[i];
            }
        }
        printf("Score %+4.2f for Move %d/%d: ", current_score, i + 1, num_possible_moves);
        print_move(possible_moves[i]);

    }

    free_board(board_copy);
    free(possible_moves);
    return best_score;
}

float maxi(Board* board, int depth, float alpha, float beta) {
    //print_board(board);
    //printf("Depth: %d",depth);
    if ( depth == 0 ) return evaluate(board);
    float max = -FLT_MAX;
        //#TODO remove magic number 64 -> more efficiant to just allocate the needed memory
    Move* possible_moves = malloc(sizeof(Move) * 200);
    if (!possible_moves) {
        fprintf(stderr, "Failed to allocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }

    int num_possible_moves = generate_all_legal_moves_for_player(board, get_current_player(board), possible_moves);
    
    //##TODO  DOes that do anything?
    // Reallocate Memory to not waste it
    possible_moves = realloc(possible_moves, sizeof(Move) * num_possible_moves);
    if (!possible_moves) {
        printf("Failed to reallocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }
    
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
        float score = mini(board_copy, depth - 1, alpha, beta);
        if( score > max ){
            max = score;
        }
        if (max >= beta) {
            break; // Beta cutoff
        }
        if (max > alpha) {
            alpha = max;
        }
    }
    free_board(board_copy);
    free(possible_moves);
    return max;
}

float mini(Board* board, int depth, float alpha, float beta) {
    //print_board(board);
    //printf("Depth: %d",depth);
    if ( depth == 0 ) return evaluate(board);
    float min = FLT_MAX;
        //#TODO remove magic number 64 -> more efficiant to just allocate the needed memory
    Move* possible_moves = malloc(sizeof(Move) * 200);
    if (!possible_moves) {
        fprintf(stderr, "Failed to allocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }

    int num_possible_moves = generate_all_legal_moves_for_player(board, get_current_player(board), possible_moves);
    
    // Reallocate Memory to not waste it
    possible_moves = realloc(possible_moves, sizeof(Move) * num_possible_moves);
    if (!possible_moves) {
        printf("Failed to reallocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }

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
        float score = maxi(board_copy, depth - 1, alpha, beta);
        if( score < min){
            min = score;
        }
        if (min <= alpha) {
            break; // Alpha cutoff
        }
        if (min < beta) {
            beta = min;
        }
    }

    free_board(board_copy);
    free(possible_moves);
    return min;
}

float evaluate(Board* board){

    float material_score = calculate_material_score(board);
    float movement_score = calculate_movement_score(board);
    //printf("%f ", movement_score);
    return material_score + movement_score;
}


float calculate_material_score(Board* board){
    float score = 0.0; 

    uint64_t temp_array[NUM_OF_BITS];

    for(int piece_type = 0; piece_type < NUM_OF_PIECE_TYPES; piece_type++){
        score += (get_piece_value(piece_type) * split_bitmap(get_all_pieces_of_type(board, piece_type), temp_array));
    }

    return score;
}

float get_piece_value(int piece_type){
    switch (piece_type) {
        case 0: return 1.0;
        case 1: return 5.0;
        case 2: return 3.0;
        case 3: return 3.0;
        case 4: return 9.0;
        case 5: return 1.0;
        case 6: return -1.0;
        case 7: return -5.0;
        case 8: return -3.0;
        case 9: return -3.0;
        case 10: return -9.0;
        case 11: return -1.0;
        default:
            printf("No Value for %i", piece_type);
            exit(EXIT_FAILURE);
    }
}


float calculate_movement_score(Board* board){
    float score = 0.0; 
    int original_player = board->current_Player;
    Move temp_array[200];
                                    // # TODO generate_all_legal_moves_for_player calls is_pseudo_legal_move
                                    // which checks if it is the players turn. 
                                    // Workaround: change the active player (inefficiant)
    board->current_Player = PLAYER_WHITE;
    int num_possible_moves_white = generate_all_legal_moves_for_player(board, PLAYER_WHITE, temp_array);
    board->current_Player = PLAYER_BLACK;
    int num_possible_moves_black = generate_all_legal_moves_for_player(board, PLAYER_BLACK, temp_array);

    board->current_Player = original_player;
    
    score = ((float) num_possible_moves_white) - ((float) num_possible_moves_black); 
    
    // 10 extra moves are worth a pawn (?)
    score = score * 0.1;

    return score;
}