

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "../header_files/board.h"


// Allocates and Initializes the necessary memory to a board
void create_board(Board** board) {
    printf("Creating Board\n");
    *board = malloc(sizeof(Board));
    (*board)->pieces = malloc(NUM_OF_ROWS * sizeof(uint64_t));
    for (int i = 0; i < NUM_OF_PIECE_TYPES; i++) {
        (*board)->pieces[i] = 0x0;
    }
    (*board)->current_Player = PLAYER_WHITE;
}


// initializes board to start position
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


// Returns bitmap of all Pieces on the Board 
uint64_t get_all_pieces(Board* board){
    uint64_t all_pieces = 0;
    for(int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        all_pieces = all_pieces | board->pieces[i];
        //printf("%d\n",board->pieces[i]);
    }
    return all_pieces; 
}





int apply_move(Board* board, Move move, int forced){
    // is_VALID Check
    
    if (forced == FORCED || is_pseudo_legal_move(board, move)){

        int piece_type = get_piece_type_at(board, move.origin);
        //printf("Piecetype moved: %d\n", piece_type);
        //printf("Origin: %s\n", get_notation_from_bitmap(move.origin));

        //remove piece from origin
        board->pieces[piece_type] = board->pieces[piece_type] & ~move.origin;
        //add piece to destination
        board->pieces[piece_type] = board->pieces[piece_type] | move.destination;
        //TODO Capture etc.

        // Changes whose turn it is:
        board->current_Player = get_opponent(board->current_Player);
        

        return 1;
    }else{
        printf("Move not legal\n");
        print_move(move);
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
    if(get_piece_type_at(board, position) <= 5) return 0;
    else return 1;
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

// TODO THis does not work

int is_in_check(Board* board, uint64_t king_pos, int king_color){
    uint64_t attackers = 0ULL;
    uint64_t possible_attackers = 0ULL;

    if (king_color == PLAYER_WHITE) {
        possible_attackers = generate_pseudolegal_moves_for_queen(board, king_pos, king_color);
        attackers |= (attackers & board->pieces[BLACK_QUEENS]);
        possible_attackers = generate_pseudolegal_moves_for_rook(board, king_pos, king_color);
        attackers |= (attackers & board->pieces[BLACK_ROOKS]);
        possible_attackers = generate_pseudolegal_moves_for_bishop(board, king_pos, king_color);
        attackers |= (attackers & board->pieces[BLACK_ROOKS]);
    }
}

// ---------- MOVE GENERATION ----------------

//TODO Should i return a bitmap or an array of moves. 

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
        for(int i = 0; i < NUM_OF_COLLUMNS; i++){   // TODO: NUM_OF_COLLUMNS only works for square boards (i think thats fine tho)
            
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
        for(int i = 0; i < NUM_OF_COLLUMNS; i++){   // TODO: NUM_OF_COLLUMNS only works for square boards (i think thats fine tho)
            
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
    // TODO initialize  possible_moves = 0; and remove the need to return possible_moves & ~position;
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
        if(~(next & own_pieces) | ~(next & opponent_pieces)) possible_moves |= next;
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

