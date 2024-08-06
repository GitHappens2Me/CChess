
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

    qsort(possible_moves, num_possible_moves, sizeof(Move), compare_moves);

    printf("Testing all %d root moves.\n", num_possible_moves);

    int best_score = (get_current_player(board) == PLAYER_WHITE) ? INT_MIN : INT_MAX;

    Board* board_copy;
    create_board(&board_copy);

    for (int i = 0; i < num_possible_moves; i++) {
        copy_board(board_copy, board);
        apply_move_forced(board_copy, possible_moves[i]);

        int current_score;
        if (get_current_player(board) == PLAYER_WHITE) {

            current_score = mini(board_copy, max_depth - 1, INT_MIN, INT_MAX);
            if (current_score >= best_score) {
                best_score = current_score;
                *best_move = possible_moves[i];
            }
        } else {

            current_score = maxi(board_copy, max_depth - 1, INT_MIN, INT_MAX);
            if (current_score <= best_score) {
                best_score = current_score;
                *best_move = possible_moves[i];
            }
        }
        printf("Score %4.2f for Move %d/%d: ", ((float)current_score / 100), i + 1, num_possible_moves);
        print_move(possible_moves[i]);
        printf("\n");

    }

    free_board(board_copy);
    free(possible_moves);
    return best_score;
}

int maxi(Board* board, int depth, int alpha, int beta) {
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
    
    //##TODO  DOes that do anything?
    // Reallocate Memory to not waste it
    /*
    possible_moves = realloc(possible_moves, sizeof(Move) * num_possible_moves);
    if (!possible_moves) {
        printf("Failed to reallocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }*/
    
    //printf("%d possible Moves - ", num_possible_moves);
    if(num_possible_moves == 0){
        free(possible_moves);
        return evaluate(board);
    }

    qsort(possible_moves, num_possible_moves, sizeof(Move), compare_moves);

    
    Board* board_copy;
    create_board(&board_copy);
    //printf("created board - ");
    for (int i = 0; i < num_possible_moves; i++) {
        copy_board(board_copy, board);
        //printf("copied board - ");
        apply_move_forced(board_copy, possible_moves[i]);
        //printf("call recursivle\n");
        int score = mini(board_copy, depth - 1, alpha, beta);
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

int mini(Board* board, int depth, int alpha, int beta) {
    //print_board(board);
    //printf("Depth: %d",depth);
    if ( depth == 0 ) return evaluate(board);
    int min = INT_MAX;
        //#TODO remove magic number 200 -> more efficiant to just allocate the needed memory
    Move* possible_moves = malloc(sizeof(Move) * 200);
    if (!possible_moves) {
        fprintf(stderr, "Failed to allocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }

    int num_possible_moves = generate_all_legal_moves_for_player(board, get_current_player(board), possible_moves);
    
    // Reallocate Memory to not waste it
    /*   
    possible_moves = realloc(possible_moves, sizeof(Move) * num_possible_moves);
    if (!possible_moves) {
        printf("Failed to reallocate memory for possible_moves\n");
        exit(EXIT_FAILURE);
    }*/

    //printf("%d possible Moves - ", num_possible_moves);
    if(num_possible_moves == 0){
        free(possible_moves);
        return evaluate(board);
    }

    qsort(possible_moves, num_possible_moves, sizeof(Move), compare_moves);

    
    Board* board_copy;
    create_board(&board_copy);
    //printf("created board - ");
    for (int i = 0; i < num_possible_moves; i++) {
        copy_board(board_copy, board);
        //printf("copied board - ");
        apply_move_forced(board_copy, possible_moves[i]);
        //printf("call recursivle\n");
        int score = maxi(board_copy, depth - 1, alpha, beta);
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

int compare_moves(const void *a, const void *b) {
    Move *moveA = (Move *)a;
    Move *moveB = (Move *)b;
    return (moveB->captured_piece_type - moveA->captured_piece_type);
}

int evaluate(Board* board){

    if(is_in_checkmate(board, PLAYER_WHITE)) return INT_MIN;
    if(is_in_checkmate(board, PLAYER_BLACK)) return INT_MAX;

    int movement_score = calculate_movement_score(board);

    int material_score = calculate_material_score(board);
    //printf("%f ", movement_score);
    return material_score + movement_score;
}


int calculate_material_score(Board* board){
    int score = 0; 

    uint64_t pieces[NUM_OF_BITS];

    for(int piece_type = 0; piece_type < NUM_OF_PIECE_TYPES; piece_type++){
        int num_of_pieces = split_bitmap(get_all_pieces_of_type(board, piece_type), pieces);
        for(int i = 0; i < num_of_pieces; i++){
            score += (get_piece_value(piece_type) + get_position_value(piece_type, pieces[i]));
        }
    }
    return score;
}

int get_piece_value(int piece_type){
    switch (piece_type) {
        // Values by Tomasz Michniewski
        case NO_PIECES: return 0;
        case WHITE_PAWNS:   return 100;
        case WHITE_KNIGHTS: return 320;
        case WHITE_BISHOPS: return 330;
        case WHITE_ROOKS:   return 500;
        case WHITE_QUEENS:  return 900;
        case WHITE_KING:    return 100;
        case BLACK_PAWNS:   return -100;
        case BLACK_KNIGHTS: return -320;
        case BLACK_BISHOPS: return -330;
        case BLACK_ROOKS:   return -500;
        case BLACK_QUEENS:  return -900;
        case BLACK_KING:    return -100;
        default:
            printf("No Value for %i", piece_type);
            exit(EXIT_FAILURE);
    }
}


int get_position_index_from_position(uint64_t position){
    for (int i = 0; i < 64; i++) {
        if (position & (1ULL << i)) {
            return (63 - i);
        }
    }
    
    return 0;
}

int calculate_movement_score(Board* board){

    int score = 0; 
    
    Move temp_array[200];
    int num_possible_moves_white = generate_all_legal_moves_for_player(board, PLAYER_WHITE, temp_array);
    int num_possible_moves_black = generate_all_legal_moves_for_player(board, PLAYER_BLACK, temp_array);

    score = (num_possible_moves_white) - (num_possible_moves_black); 
    
    // 10 extra moves are worth a pawn (?)
    return (score * 10);

}



int get_position_value(int piece_type, uint64_t position){

    // #TODO use costants (WHITE PAWNS etc.) to make this function more flexible

    int piece_position_tables[NUM_OF_PIECE_TYPES][64] = {

    //NO_PIECES
    { 0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0,
      0,  0,  0,  0,  0,  0,  0,  0},
      
    //WHITE_PAWNS
    { 0,  0,  0,  0,  0,  0,  0,  0, 
     50, 50, 50, 50, 50, 50, 50, 50, 
     10, 10, 20, 30, 30, 20, 10, 10, 
      5,  5, 10, 25, 25, 10,  5,  5,
      0,  0,  0, 20, 20,  0,  0,  0,
      5, -5,-10,  0,  0,-10, -5,  5,
      5, 10, 10,-20,-20, 10, 10,  5,
      0,  0,  0,  0,  0,  0,  0,  0},
    
    //WHITE_ROOKS
    { 0,  0,  0,  0,  0,  0,  0,  0,
      5, 10, 10, 10, 10, 10, 10,  5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
      0,  0,  0,  5,  5,  0,  0,  0},
    
    //WHITE_KNIGHTS
    {-50,-40,-30,-30,-30,-30,-40,-50,
     -40,-20,  0,  0,  0,  0,-20,-40,
     -30,  0, 10, 15, 15, 10,  0,-30,
     -30,  5, 15, 20, 20, 15,  5,-30,
     -30,  0, 15, 20, 20, 15,  0,-30,
     -30,  5, 10, 15, 15, 10,  5,-30,
     -40,-20,  0,  5,  5,  0,-20,-40,
     -50,-40,-30,-30,-30,-30,-40,-50},
    
    //WHITE_BISHOPS
    { -20,-10,-10,-10,-10,-10,-10,-20,
      -10,  0,  0,  0,  0,  0,  0,-10,
      -10,  0,  5, 10, 10,  5,  0,-10,
      -10,  5,  5, 10, 10,  5,  5,-10,
      -10,  0, 10, 10, 10, 10,  0,-10,
      -10, 10, 10, 10, 10, 10, 10,-10,
      -10,  5,  0,  0,  0,  0,  5,-10,
      -20,-10,-10,-10,-10,-10,-10,-20},
    
    //WHITE_QUEENS
    {-20,-10,-10, -5, -5,-10,-10,-20,
     -10,  0,  0,  0,  0,  0,  0,-10,
     -10,  0,  5,  5,  5,  5,  0,-10,
      -5,  0,  5,  5,  5,  5,  0, -5,
       0,  0,  5,  5,  5,  5,  0, -5,
     -10,  5,  5,  5,  5,  5,  0,-10,
     -10,  0,  5,  0,  0,  0,  0,-10,
     -20,-10,-10, -5, -5,-10,-10,-20},

    //WHITE_KING
    {-30,-40,-40,-50,-50,-40,-40,-30,
     -30,-40,-40,-50,-50,-40,-40,-30,
     -30,-40,-40,-50,-50,-40,-40,-30,
     -30,-40,-40,-50,-50,-40,-40,-30,
     -20,-30,-30,-40,-40,-30,-30,-20,
     -10,-20,-20,-20,-20,-20,-20,-10,
      20, 20,  0,  0,  0,  0, 20, 20,
      20, 30, 10,  0,  0, 10, 30, 20},
        
    //BLACK_PAWNS
    { 0,  0,  0,  0,  0,  0,  0,  0,
     -5,-10,-10, 20, 20,-10,-10, -5,
     -5,  5, 10,  0,  0, 10,  5, -5,
      0,  0,  0,-20,-20,  0,  0,  0, 
     -5, -5,-10,-25,-25,-10, -5, -5,
    -10,-10,-20,-30,-30,-20,-10,-10,
    -50,-50,-50,-50,-50,-50,-50,-50,
      0,  0,  0,  0,  0,  0,  0,  0},
    
    //BLACK_ROOKS
    { 0,  0,  0, -5, -5,  0,  0,  0,
      5,  0,  0,  0,  0,  0,  0,  5,
      5,  0,  0,  0,  0,  0,  0,  5,
      5,  0,  0,  0,  0,  0,  0,  5, 
      5,  0,  0,  0,  0,  0,  0,  5,
      5,  0,  0,  0,  0,  0,  0,  5, 
     -5,-10,-10,-10,-10,-10,-10, -5,
      0,  0,  0,  0,  0,  0,  0,  0},
    
    //BLACK_KNIGHTS
    { 50, 40, 30, 30, 30, 30, 40, 50,
      40, 20,  0, -5, -5,  0, 20, 40,
      30, -5,-10,-15,-15,-10, -5, 30,
      30,  0,-15,-20,-20,-15,  0, 30,
      30, -5,-15,-20,-20,-15, -5, 30,
      30,  0,-10,-15,-15,-10,  0, 30,
      40, 20,  0,  0,  0,  0, 20, 40,
      50, 40, 30, 30, 30, 30, 40, 50},
    
    //BLACK_BISHOPS
    { 20, 10, 10, 10, 10, 10, 10, 20,
      10, -5,  0,  0,  0,  0, -5, 10,
      10,-10,-10,-10,-10,-10,-10, 10,
      10,  0,-10,-10,-10,-10,  0, 10, 
      10, -5, -5,-10,-10, -5, -5, 10, 
      10,  0, -5,-10,-10, -5,  0, 10, 
      10,  0,  0,  0,  0,  0,  0, 10, 
      20, 10, 10, 10, 10, 10, 10, 20},

    //BLACK_QUEENS
    { 20, 10, 10,  5,  5, 10, 10, 20,
      10,  0, -5,  0,  0,  0,  0, 10, 
      10, -5, -5, -5, -5, -5,  0, 10,  
       0,  0, -5, -5, -5, -5,  0,  5,  
       5,  0, -5, -5, -5, -5,  0,  5, 
      10,  0, -5, -5, -5, -5,  0, 10, 
      10,  0,  0,  0,  0,  0,  0, 10,
      20, 10, 10,  5,  5, 10, 10, 20},

    //BLACK_KING
    {-20,-30,-10,  0,  0,-10,-30,-20,
     -20,-20,  0,  0,  0,  0,-20,-20,
      10, 20, 20, 20, 20, 20, 20, 10,
      20, 30, 30, 40, 40, 30, 30, 20,
      30, 40, 40, 50, 50, 40, 40, 30,
      30, 40, 40, 50, 50, 40, 40, 30,
      30, 40, 40, 50, 50, 40, 40, 30, 
      30, 40, 40, 50, 50, 40, 40, 30} };


    return piece_position_tables[piece_type][get_position_index_from_position(position)];

}