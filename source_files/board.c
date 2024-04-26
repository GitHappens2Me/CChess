#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "../header_files/main.h"
#include "../header_files/board.h"
#include "../header_files/move.h"
#include "../header_files/inout.h"


// Allocates the necessary memory to a board
void create_board(Board** board){
    printf("Creating Board\n");
    *board = ( Board *)malloc(sizeof(Board));
    (*board)->pieces = (int64_t *)malloc(NUM_OF_ROWS * sizeof(int64_t));
    for(int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        (*board)->pieces[i] = 0x0;
    }
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

uint64_t get_all_pieces(Board* board){
    uint64_t all_pieces = 0;
    for(int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        all_pieces = all_pieces | board->pieces[i];
        printf("%d\n",board->pieces[i]);
    }
    return all_pieces; 
}


int apply_move(Board* board, Move move){
    // is_VALID Check
    if (1){
        //remove piece from origin
        board->pieces[move.piece_type] = board->pieces[move.piece_type] & ~move.origin;
        //add piece to destination
        board->pieces[move.piece_type] = board->pieces[move.piece_type] | move.destination;
        //TODO Capture etc.
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

//TODO Should i return a bitmap or an array of moves. 
uint64_t generate_legal_moves_for_piece(Board* board, uint64_t position){
    switch(get_piece_type_at(board, position)){
        case WHITE_PAWNS:
        case BLACK_PAWNS: 

        case WHITE_ROOKS: return generate_pseudolegal_moves_for_rook(board, position, PLAYER_WHITE);
        case BLACK_ROOKS: return generate_pseudolegal_moves_for_rook(board, position, PLAYER_BLACK);

        case WHITE_KNIGHTS:
        case BLACK_KNIGHTS: 

        case WHITE_BISHOPS: return generate_pseudolegal_moves_for_bishop(board, position, PLAYER_WHITE);
        case BLACK_BISHOPS: return generate_pseudolegal_moves_for_bishop(board, position, PLAYER_BLACK);

        case WHITE_QUEENS:
        case BLACK_QUEENS:

        case WHITE_KING:
        case BLACK_KING: 

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
            if     (shift_direction[direction] == LEFT ) next <<= shift_amount[direction];
            else if(shift_direction[direction] == RIGHT) next >>= shift_amount[direction];
            // Collision with own piece
            if(next & own_pieces){
                break;
            // Collision with opponent piece or H-FILE reached
            }else if(next & opponent_pieces || next & edges[direction]){
                possible_moves |= next;
                break;
            // No Collision
            }else{
                possible_moves |= next;
            }
        }
    next = position;
    }

    return possible_moves;
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
            if     (shift_direction[direction] == LEFT ) next <<= shift_amount[direction];
            else if(shift_direction[direction] == RIGHT) next >>= shift_amount[direction];
            // Collision with own piece
            if(next & own_pieces){
                break;
            // Collision with opponent piece or H-FILE reached
            }else if(next & opponent_pieces || next & edges_horizontal[direction] || next & edges_vertical[direction]){
                possible_moves |= next;
                break;
            // No Collision
            }else{
                possible_moves |= next;
            }
        }
    next = position;
    }

    return possible_moves;
}

int get_opponent(int player){
    if(player == PLAYER_BLACK) return PLAYER_WHITE;
    if(player == PLAYER_WHITE) return PLAYER_BLACK;
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




/*
alter rook code:
uint64_t generate_pseudolegal_moves_for_rook(Board* board, uint64_t position, int player){
    uint64_t possible_moves = position;
    uint64_t opponent_pieces = get_pieces_of_player(board, get_opponent(player));
    uint64_t own_pieces = get_pieces_of_player(board, player);
    uint64_t next = position;

 // Sliding to the right
    for(int i = 0; i < NUM_OF_COLLUMNS; i++){
        next >>= 1;
        // Collision with own piece
        if(next & own_pieces){
            break;
        // Collision with opponent piece or H-FILE reached
        }else if(next & opponent_pieces || next & COLLUMN_h){
            possible_moves |= next;
            break;
        // No Collision
        }else{
            possible_moves |= next;
        }
    }
    next = position;

    // Sliding to the right
    for(int i = 0; i < NUM_OF_COLLUMNS; i++){
        next <<= 1;
        // Collision with own piece
        if(next & own_pieces){
            break;
        // Collision with opponent piece or A-FILE reached
        }else if(next & opponent_pieces || next & COLLUMN_a){
            possible_moves |= next;
            break;
        // No Collision
        }else{
            possible_moves |= next;
        }
    }
    next = position;
    
    // Sliding down
    for(int i = 0; i < NUM_OF_ROWS; i++){
        next >>= 8;
        // Collision with own piece
        if(next & own_pieces){
            break;
        // Collision with opponent piece or ROW_1 reached
        }else if(next & opponent_pieces || next & ROW_1){
            possible_moves |= next;
            break;
        // No Collision
        }else{
            possible_moves |= next;
        }
    }
    next = position;

    // Sliding up
    for(int i = 0; i < NUM_OF_ROWS; i++){
        next <<= 8;
        // Collision with own piece
        if(next & own_pieces){
            break;
        // Collision with opponent piece or ROW_8
        }else if(next & opponent_pieces || next & ROW_8){
            possible_moves |= next;
            break;
        // No Collision
        }else{
            possible_moves |= next;
        }
    }
    

    return possible_moves;

*/