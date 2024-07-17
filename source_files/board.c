

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

#include "../header_files/board.h"
#include "../header_files/inout.h"


// Allocates and Initializes the necessary memory to a board
void create_board(Board** board) {
    //printf("Creating Board\n");
    *board = malloc(sizeof(Board));
    if (*board == NULL) {
        fprintf(stderr, "Failed to allocate memory for board\n");
        exit(EXIT_FAILURE);
    }
    (*board)->pieces = malloc(NUM_OF_PIECE_TYPES * sizeof(uint64_t));
    if ((*board)->pieces == NULL) {
        fprintf(stderr, "Failed to allocate memory for pieces array\n");
        free(*board);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < NUM_OF_PIECE_TYPES; i++) {
        (*board)->pieces[i] = 0x0;
    }
    (*board)->current_Player = PLAYER_WHITE;
}

void free_board(Board* board) {
    if (board != NULL) {
        free(board->pieces);
        free(board);
    }
}


void copy_board(Board* copy, Board* source) {
    if (copy == NULL) {
        fprintf(stderr, "Must Allocate Memory in order to copy a board\n");
        exit(EXIT_FAILURE);
    }
    //printf("Copying Board\n");
    copy->pieces = malloc(NUM_OF_PIECE_TYPES * sizeof(uint64_t));
    if (copy->pieces == NULL) {
        fprintf(stderr, "Failed to allocate memory for pieces array\n");
        exit(EXIT_FAILURE);
    }
    memcpy(copy->pieces, source->pieces, NUM_OF_PIECE_TYPES * sizeof(uint64_t));
    copy->current_Player = source->current_Player;
}



// Initialize board to start position
void initialize_board(Board* board){
    printf("Initializing Board\n");
    board->pieces[WHITE_PAWNS] = 0x000000000000FF00;
    board->pieces[WHITE_ROOKS] = 0x0000000000000081;
    board->pieces[WHITE_KNIGHTS] = 0x0000000000000042;
    board->pieces[WHITE_BISHOPS] = 0x0000000000000024;
    board->pieces[WHITE_QUEENS] = 0x0000000000000010;
    board->pieces[WHITE_KING] = 0x0000000000000008;

    board->pieces[BLACK_PAWNS] = 0x00FF000000000000;
    board->pieces[BLACK_ROOKS] = 0x8100000000000000;
    board->pieces[BLACK_KNIGHTS] = 0x4200000000000000;
    board->pieces[BLACK_BISHOPS] = 0x2400000000000000;
    board->pieces[BLACK_QUEENS] = 0x1000000000000000;
    board->pieces[BLACK_KING] = 0x0800000000000000;
}

void initialize_board_FEN(Board* board, char* fen_string){
    //printf("Initializing Board to %s\n", fen_string);

    // Delete all pieces from board:
    for (int i = 0; i < NUM_OF_PIECE_TYPES; i++) {
        board->pieces[i] = 0x0;
    }

    // Elements of a FEN String [Pieces, active player, castling rights, en passant square, halvemove clock, fullmove clock]
    char* element = strtok(fen_string, " ");

    // Iterates through all 8 ranks (8 -> 1)
    char* rank = strtok(element, "/");

    uint64_t rank_mask = ROW_8; 

    while( rank != NULL ) {
        //printf("%s\n", rank );
        
        uint64_t collumn_mask = COLLUMN_a;
        int piece = 0;
        while (rank[piece] != '\0') {
            //printf("%d: %c\n", piece, rank[piece]);
        
            //printf("Collumn:\n");
            //print_position(collumn_mask);

            if(isalpha(rank[piece])){  
                // Using rank_mask & collumn as mask set the corresponsing bit on the board
                board->pieces[get_piecetype_for_symbol(rank[piece])] |= (rank_mask & collumn_mask); 
                collumn_mask >>= 1; // moves current collumn (/file) right one

            }else if(isdigit(rank[piece])){
                collumn_mask >>= (rank[piece] - '0'); // moves current collumn (/file) right the specified number of squares 

            }
            piece++;
        }

        rank = strtok(NULL, "/");
        
        // moves current rank down one 
        rank_mask >>= 8;
    }


    // Initialize secondary information (e.g: w KQkq - 0 1) 
    //                                  (player, castling, en passant, halvmove clock, fullmove clock     )

    

}


// Returns bitmap of all Pieces on the Board 
uint64_t get_all_pieces(Board* board){
    uint64_t all_pieces = 0;
    for(int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        all_pieces = all_pieces | board->pieces[i];
        //printf("%d\n",board->pieces[i]);
    }
    return all_pieces; 
}


int results_in_check(Board* board, Move move){
    //printf("Checking if move results in Check\n");
    Board* board_copy;
    create_board(&board_copy);
    copy_board(board_copy, board);

    int player_color = board_copy->current_Player;

    apply_move_forced(board_copy, move);

    if(is_in_check(board_copy, player_color)){
        printf("player %d is in check after that move\n", player_color );
    }

    int results_in_check = is_in_check(board_copy, player_color);

    free_board(board_copy);

    return results_in_check;
}

// applies the move without checks for validity
void apply_move_forced(Board* board, Move move){
    int piece_type = get_piece_type_at(board, move.origin);
    //printf("Piecetype moved: %d\n", piece_type);
    //printf("Origin: %s\n", get_notation_from_bitmap(move.origin));


    // For Captures
    if(move.destination & get_all_pieces(board)){
        printf("Capture!");
        int captured_piece_type = get_piece_type_at(board, move.destination);
        // remove captured piece
        board->pieces[captured_piece_type] = board->pieces[captured_piece_type] & ~move.destination;
    }
     // remove piece from origin
    board->pieces[piece_type] = board->pieces[piece_type] & ~move.origin;
    // add piece to destination
    board->pieces[piece_type] = board->pieces[piece_type] | move.destination;
    // Changes whose turn it is:
    board->current_Player = get_opponent(board->current_Player);
}

int apply_move(Board* board, Move move){

    if (is_legal_move(board, move)){

        apply_move_forced(board, move);
        return 1;

    }else{
        printf("Move not valid. Please choose a different Move\n");
        return 0;
    }
}


uint64_t get_pieces_of_player(Board* board, int player){
    uint64_t all_pieces = 0;
    if(player == PLAYER_WHITE){
        for(int i = 0; i < 6; i++){
            all_pieces = all_pieces | board->pieces[i];
        }
    }else if(player == PLAYER_BLACK){
        for(int i = 6; i < 12; i++){
            all_pieces = all_pieces | board->pieces[i];
        }
    }
    return all_pieces; 
}




int get_opponent(int player){
    if(player == PLAYER_BLACK) return PLAYER_WHITE;
    if(player == PLAYER_WHITE) return PLAYER_BLACK;
}

int get_piece_color(Board *board, uint64_t position){
    if(get_piece_type_at(board, position) <= 5) return PLAYER_WHITE;
    else return PLAYER_BLACK;
}

int get_current_player(Board *board){
    return board->current_Player;
}



int get_piece_type_at(Board* board, uint64_t position){
    for(int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        if((board->pieces[i] & position) != 0){
            //print_position(board->pieces[i] & position);
            return i;
        }
    }
    return -1;
}

uint64_t get_all_pieces_of_type(Board* board, int piece_type){
    return board->pieces[piece_type];
}

int split_bitmap(uint64_t pieces, uint64_t* indivdual_pieces){

    int number_of_bits = NUM_OF_BITS; 
    int counter = 0;
    uint64_t indivdual_piece = 1ULL;

    for (int i = 0; i < number_of_bits; i++) {
        // Check if the current bit is set
        if (pieces & indivdual_piece){
            indivdual_pieces[counter] = indivdual_piece;
            counter++;
        }else{
            // this resets the unused rest of indivdual_pieces to all zeroes
            indivdual_pieces[i] = 0ULL;
        }
        indivdual_piece <<= 1;
    }
    return counter;
}


int is_in_check(Board* board, int king_color){
    int king_piece_index = -1;
    if(king_color == PLAYER_WHITE){
         king_piece_index = WHITE_KING;
    }else{ 
        king_piece_index = BLACK_KING;
    }

    return is_attacked(board, board->pieces[king_piece_index], get_opponent(king_color));
}

/*
 * tests if a specified square is attacked by the specified player
 *
 *  b: board, on which is being tested
 *  position: square, which is tested
 *  attacking_color: color of the (potentially) attacking player
 *
 *  returns: 
 *           1, if square is attacked
 *           0, if square is not attacked
 * 
 *  notes: 
 * 
 *  #TODO: Include Pawns (and the Opponent King) in the test
 */
int is_attacked(Board* board, uint64_t position, int attacking_color){
    
    uint64_t bishop_attack_path = generate_pseudolegal_moves_for_bishop(board, position, get_opponent(attacking_color));
    uint64_t rook_attack_path = generate_pseudolegal_moves_for_rook(board, position, get_opponent(attacking_color));
    uint64_t knight_attack_path = generate_pseudolegal_moves_for_knight(board, position, get_opponent(attacking_color));
 
    if(attacking_color == PLAYER_WHITE){
        if((bishop_attack_path & get_all_pieces_of_type(board, WHITE_BISHOPS)) || (bishop_attack_path & get_all_pieces_of_type(board, WHITE_QUEENS))) return 1;
        if((rook_attack_path & get_all_pieces_of_type(board, WHITE_ROOKS)) || (rook_attack_path & get_all_pieces_of_type(board, WHITE_QUEENS))) return 1;
        if((knight_attack_path & get_all_pieces_of_type(board, WHITE_KNIGHTS))) return 1;
    }
    else{
        if((bishop_attack_path & get_all_pieces_of_type(board, BLACK_BISHOPS)) || (bishop_attack_path & get_all_pieces_of_type(board, BLACK_QUEENS))) return 1;
        if((rook_attack_path & get_all_pieces_of_type(board, BLACK_ROOKS)) || (rook_attack_path & get_all_pieces_of_type(board, BLACK_QUEENS))) return 1;
        if((knight_attack_path & get_all_pieces_of_type(board, BLACK_KNIGHTS))) return 1;
    }

}

// ---------- MOVE GENERATION ----------------


int generate_all_legal_moves_for_player(Board* board, int player, Move* legal_moves){
    printf("PLAYER %d", player);
    if(legal_moves == NULL){
        fprintf(stderr, "Must Allocate Memory for all legal Moves\n");
        exit(EXIT_FAILURE);
    }

    int move_counter = 0;


    int pawn_index = 0;
    int king_index = 5;
    if(player == PLAYER_BLACK){
        pawn_index = 6;
        king_index = 11;
    }

    // Looping through all the piece_types of the player
    for(int piece_type = pawn_index; piece_type <= king_index; piece_type++){
        // This array holds the position of all individual pieces of the piece_type
        uint64_t* indivdual_pieces = malloc(sizeof(uint64_t) * 64);

        int num_of_pieces = split_bitmap(board->pieces[piece_type], indivdual_pieces);
        printf("\nFor piecetype %c, there are %d pieces\n", get_symbol_for_piecetype(piece_type), num_of_pieces);

        // Looping trough all the pieces of that type
        for(int piece = 0; piece < num_of_pieces; piece++){
            uint64_t piece_position = indivdual_pieces[piece];

            Move* legal_moves_by_piece = malloc(sizeof(uint64_t) * 30);
            int num_of_moves_by_piece = generate_legal_moves_for_piece(board, piece_position,legal_moves_by_piece);
            printf("For piece %d of piece_type %c, there are %d moves\n", piece, get_symbol_for_piecetype(piece_type), num_of_moves_by_piece);
            
            // Append all moves by the piece to legal_moves
            for(int i = move_counter; i < move_counter + num_of_moves_by_piece; i++){
                legal_moves[i] = legal_moves_by_piece[i - move_counter];
            }
            move_counter += num_of_moves_by_piece;
        }
    }
    
    return move_counter;
}


int generate_legal_moves_for_piece(Board* board, uint64_t position, Move* legal_moves_by_piece){

    int move_counter = 0;

    if (legal_moves_by_piece == NULL) {
        fprintf(stderr, "Must Allocate Memory for legal_moves\n");
        exit(EXIT_FAILURE);
    }

    uint64_t pseudolegal_destinations = generate_pseudolegal_moves_for_piece(board, position);

    Move* pseudolegal_moves = malloc(sizeof(uint64_t) * 30);
    int num_of_pseudolegal_moves = get_moves_from_destination_bitmap(position, pseudolegal_destinations, pseudolegal_moves);
    
    for(int i = 0; i < num_of_pseudolegal_moves; i++){
        if(is_legal_move(board, pseudolegal_moves[i])){
            legal_moves_by_piece[move_counter] = pseudolegal_moves[i];
            move_counter++;
        }
    }
    //printf("From %d pseudolegal moves, %d are legal.\n", num_of_pseudolegal_moves, move_counter);
    return move_counter;
}

uint64_t generate_pseudolegal_moves_for_piece(Board* board, uint64_t position){
    switch(get_piece_type_at(board, position)){
        case WHITE_PAWNS: return generate_pseudolegal_moves_for_pawn(board, position, PLAYER_WHITE);
        case BLACK_PAWNS: return generate_pseudolegal_moves_for_pawn(board, position, PLAYER_BLACK);

        case WHITE_ROOKS: return generate_pseudolegal_moves_for_rook(board, position, PLAYER_WHITE);
        case BLACK_ROOKS: return generate_pseudolegal_moves_for_rook(board, position, PLAYER_BLACK);

        case WHITE_KNIGHTS: return generate_pseudolegal_moves_for_knight(board, position, PLAYER_WHITE);
        case BLACK_KNIGHTS: return generate_pseudolegal_moves_for_knight(board, position, PLAYER_BLACK);

        case WHITE_BISHOPS: return generate_pseudolegal_moves_for_bishop(board, position, PLAYER_WHITE);
        case BLACK_BISHOPS: return generate_pseudolegal_moves_for_bishop(board, position, PLAYER_BLACK);

        case WHITE_QUEENS: return generate_pseudolegal_moves_for_queen(board, position, PLAYER_WHITE);
        case BLACK_QUEENS: return generate_pseudolegal_moves_for_queen(board, position, PLAYER_BLACK);

        case WHITE_KING: return generate_pseudolegal_moves_for_king(board, position, PLAYER_WHITE);
        case BLACK_KING: return generate_pseudolegal_moves_for_king(board, position, PLAYER_BLACK);

        default:    //printf("No piece at position\n"); 
                    return 0ULL;
    }
}


uint64_t generate_pseudolegal_moves_for_rook(Board* board, uint64_t position, int player){
    uint64_t possible_moves = position;
    uint64_t opponent_pieces = get_pieces_of_player(board, get_opponent(player));
    uint64_t own_pieces = get_pieces_of_player(board, player);
    uint64_t next = position;

    // parameters for {right, left, down, up}
    int shift_direction[] = {RIGHT, LEFT, RIGHT, LEFT};
    int shift_amount[] = {1, 1, 8, 8};
    uint64_t edges[] = {COLLUMN_h, COLLUMN_a, ROW_1, ROW_8};

    // move in all direction
    for(int direction = 0; direction < 4; direction++){
        for(int i = 0; i < NUM_OF_COLLUMNS; i++){   

            // Prevent moving of the board
            if(next & edges[direction]) break;
            
            if     (shift_direction[direction] == LEFT ) next <<= shift_amount[direction];
            else if(shift_direction[direction] == RIGHT) next >>= shift_amount[direction];
            // Collision with own piece
            if(next & own_pieces){
                break;
            // Collision with opponent piece
            }else if(next & opponent_pieces){
                possible_moves |= next;
                break;
            // No Collision
            }else{
                possible_moves |= next;
            }
        }
        next = position;
    }

    // removes original position from possibles squares to move to
    return possible_moves & ~position;
}

uint64_t generate_pseudolegal_moves_for_bishop(Board* board, uint64_t position, int player){
    uint64_t possible_moves = position;
    uint64_t opponent_pieces = get_pieces_of_player(board, get_opponent(player));
    uint64_t own_pieces = get_pieces_of_player(board, player);
    uint64_t next = position;

    // parameters for {down-right, down-left, up-left, up-right}
    int shift_direction[] = {RIGHT, RIGHT, LEFT, LEFT};
    int shift_amount[] = {9, 7, 9, 7};
    uint64_t edges_vertical[] = {ROW_1, ROW_1, ROW_8, ROW_8};
    uint64_t edges_horizontal[] = {COLLUMN_h, COLLUMN_a, COLLUMN_a, COLLUMN_h};

    // move in all direction
    for(int direction = 0; direction < 4; direction++){
        for(int i = 0; i < NUM_OF_COLLUMNS; i++){   

            // prevent moving of the board
            if(next & edges_horizontal[direction] || next & edges_vertical[direction]) break;
                
            if     (shift_direction[direction] == LEFT ) next <<= shift_amount[direction];
            else if(shift_direction[direction] == RIGHT) next >>= shift_amount[direction];
            // Collision with own piece
            if(next & own_pieces){
                break;
            // Collision with opponent piece
            }else if(next & opponent_pieces ){
                possible_moves |= next;
                break;
            // No Collision
            }else{
                possible_moves |= next;
            }
        }
        next = position;
    }
    // removes original position from possibles squares to move to
    return possible_moves & ~position;
}

uint64_t generate_pseudolegal_moves_for_knight(Board* board, uint64_t position, int player){
    uint64_t possible_moves = position;
    uint64_t opponent_pieces = get_pieces_of_player(board, get_opponent(player));
    uint64_t own_pieces = get_pieces_of_player(board, player);
    uint64_t next = position;

    /*
           2 3
          1   4
            N 
          8   5
           7 6  
    */
    // parameters for:            {1,         2,         3,         4,         5,         6,         7,         8}(see diagramm above):
    int shift_direction[] =       {LEFT,      LEFT,      LEFT,      LEFT,      RIGHT,     RIGHT,     RIGHT,     RIGHT};
    int shift_amount[] =          {10,        17,        15,        6,         10,        17,        15,        6};
    uint64_t edges_vertical[] =   {ROW_8,     ROW_8,     ROW_8,     ROW_8,     ROW_1,     ROW_1,     ROW_1,     ROW_1};
    uint64_t edges_horizontal[] = {COLLUMN_a, COLLUMN_a, COLLUMN_h, COLLUMN_h, COLLUMN_h, COLLUMN_h, COLLUMN_a, COLLUMN_a};
    uint64_t edges_spacer[] =     {COLLUMN_b, ROW_7,     ROW_7,     COLLUMN_g, COLLUMN_g, ROW_2,     ROW_2,     COLLUMN_b}; // the knight moves 2 squares in a given direction so we need to check if it can move off the board
    

    // move in all direction
    for(int direction = 0; direction < 8; direction++){
        next = position;

        // Prevent knight from moving over the edge of the board
        if(next & edges_vertical[direction]  || next & edges_horizontal[direction] || next & edges_spacer[direction]){
            continue;
        }
        if     (shift_direction[direction] == LEFT ) next <<= shift_amount[direction];
        else if(shift_direction[direction] == RIGHT) next >>= shift_amount[direction];
        // Collision with own piece

        if(next & own_pieces){
            continue;
        
        // Collision with opponent piece

        }else if(next & opponent_pieces){       
            possible_moves |= next;
            continue;
        // No Collision
        }else{
            possible_moves |= next;
        }
    }

    // removes original position from possibles squares to move to 
    return possible_moves & ~position;

}

uint64_t generate_pseudolegal_moves_for_queen(Board* board, uint64_t position, int player){
    return generate_pseudolegal_moves_for_bishop(board, position, player) | generate_pseudolegal_moves_for_rook(board, position, player);
}

uint64_t generate_pseudolegal_moves_for_king(Board* board, uint64_t position, int player){
    // TODO Idea: initialize  possible_moves = 0; and remove the need to return possible_moves & ~position;
    // Also in the other functions
    uint64_t possible_moves = position;
    uint64_t opponent_pieces = get_pieces_of_player(board, get_opponent(player));
    uint64_t own_pieces = get_pieces_of_player(board, player);
    uint64_t next = position;

    /*
          234
          1K5
          876 
    */
    // parameters for:            {1,         2,         3,         4,         5,         6,         7,         8}(see diagramm above):
    int shift_direction[] =       {LEFT,      LEFT,      LEFT,      LEFT,      RIGHT,     RIGHT,     RIGHT,     RIGHT};
    int shift_amount[] =          {1,         9,         8,         7,         1,         9,         8,         7};
    uint64_t edges_vertical[] =   {0,         ROW_8,     ROW_8,     ROW_8,     0,         ROW_1,     ROW_1,     ROW_1};
    uint64_t edges_horizontal[] = {COLLUMN_a, COLLUMN_a, 0,         COLLUMN_h, COLLUMN_h, COLLUMN_h, 0,         COLLUMN_a};


    // move in all direction
    for(int direction = 0; direction < 8; direction++){
        next = position;

        // Prevent knight from moving over the edge of the board
        if(next & edges_vertical[direction]  || next & edges_horizontal[direction]){
            continue;
        }
        if     (shift_direction[direction] == LEFT ) next <<= shift_amount[direction];
        else if(shift_direction[direction] == RIGHT) next >>= shift_amount[direction];
        // Collision with own piece

        if(next & own_pieces){
            continue;
        
        // Collision with opponent piece

        }else if(next & opponent_pieces){       
            possible_moves |= next;
            continue;
        // No Collision
        }else{
            possible_moves |= next;
        }
    }



    // removes original position from possibles squares to move to
    return possible_moves & ~position;

}


// TODO Refactor and improve ALL move generation: 
// replace if-clause with clever bit operations
//#BUG pawns can capture forwards when moving 2 squares 
uint64_t generate_pseudolegal_moves_for_pawn(Board* board, uint64_t position, int player){
    uint64_t possible_moves = position;
    uint64_t opponent_pieces = get_pieces_of_player(board, get_opponent(player));
    uint64_t own_pieces = get_pieces_of_player(board, player);
    uint64_t next = position;

    uint64_t start_row;
    int shift_direction;
    int shift_amount_diagonal[] = {7,9};  

    if(player == PLAYER_WHITE){
        start_row = ROW_2;
        shift_direction = LEFT;
    }else if(player == PLAYER_BLACK){
        start_row = ROW_7;
        shift_direction = RIGHT;
    }

    if(shift_direction == LEFT) next <<= 8;
    if(shift_direction == RIGHT) next >>= 8;

    if(!(next & (opponent_pieces | own_pieces))) possible_moves |= next;

    // double move if not moved yet
    if(position & start_row){
        if(shift_direction == LEFT) next <<= 8;
        if(shift_direction == RIGHT) next >>= 8;
        if(!((next & own_pieces) | (next & opponent_pieces)) ) possible_moves |= next;
        
    }


    // Captures 
    if(shift_direction == LEFT){
        // to the right
        next = position << 7;
        if((next & opponent_pieces) && !(position & COLLUMN_h)) possible_moves |= next;
        // to the left
        next = position << 9;
        if((next & opponent_pieces) && !(position & COLLUMN_a)) possible_moves |= next;
    }else if(shift_direction == RIGHT){
        // to the left
        next = position >> 7;
        if((next & opponent_pieces) && !(position & COLLUMN_a)) possible_moves |= next;
        // to the right
        next = position >> 9;
        if((next & opponent_pieces) && !(position & COLLUMN_h)) possible_moves |= next;
    }
    
    return possible_moves & ~position;
}

