#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../header_files/main.h"
#include "../header_files/board.h"
#include "../header_files/inout.h"



/*
 *  outputs the position of all instances of a specified piecetype to console
 *
 *  board: the board which pieces are displayed
 *  piecetype: the type of piece to be displayed (0 - 11) 
 *      See const definitions in board.h.
 * 
 *  returns: void
 */
void print_pieces(Board* board, int piecetype){

   //uint64_t all_pieces = get_all_pieces(board);
    uint64_t all_pieces = board->pieces[piecetype];

    // Determine the number of bits in an int64_t
    int numBits = sizeof(all_pieces) * 8;
    
    // Iterate through each bit from left to right
    for (int i = numBits - 1; i >= 0; i--) {
        // Check if the current bit is set
        if (all_pieces & ((uint64_t)1 << i))
            printf("1");
        else
            printf("0");

        if(i % 8 == 0){
            printf("\n");
        }
    }
    printf("\n");
}

/*
 *  outputs the position of all pieces to console
 *  using the get_symbol_for_piecetype function to translate from piece_type to symbol
 *  e.g.  0 (WHITE_PAWNS) -> P  
 *        6 (BLACK_PAWNS) -> p 
 * 
 *  board: the board which pieces are displayed
 * 
 *  returns: void
 */
void print_board(Board* board){
    char str_board[NUM_OF_BITS + 1];
    memset(str_board, '.', NUM_OF_BITS); // Initialize the board with spaces
    str_board[NUM_OF_BITS] = '\0'; // Null terminate the string
    
    for(int piece_type = 0; piece_type < NUM_OF_PIECE_TYPES; piece_type++){
        uint64_t current_pieces = board->pieces[piece_type];
        for (int i = NUM_OF_BITS - 1; i >= 0; i--) {   
            if (current_pieces & ((uint64_t)1 << i)){
                str_board[NUM_OF_BITS - 1 - i] = get_symbol_for_piecetype(piece_type);
            }  
        }
    }
    printf("\n");
    for(size_t i = 0; i < strlen(str_board); i++){
        printf("%c", str_board[i]);
        if((i+1) % NUM_OF_COLLUMNS == 0) printf("\n");
    }
    printf("\n");
}

char get_symbol_for_piecetype(int piece_type){
    switch (piece_type) {
        case 0: return 'P';
        case 1: return 'R';
        case 2: return 'N';
        case 3: return 'B';
        case 4: return 'Q';
        case 5: return 'K';
        case 6: return 'p';
        case 7: return 'r';
        case 8: return 'n';
        case 9: return 'b';
        case 10: return 'q';
        case 11: return 'k';
        default:
            printf("No piece-symbol for %i", piece_type);
            exit(EXIT_FAILURE);
    }
}

int get_piecetype_for_symbol(char symbol){
    switch (symbol) {
        case 'P':  return 0;
        case 'R':  return 1;
        case 'N':  return 2;
        case 'B':  return 3;
        case 'Q':  return 4;
        case 'K':  return 5;
        case 'p':  return 6;
        case 'r':  return 7;
        case 'n':  return 8;
        case 'b':  return 9;
        case 'q': return 10;
        case 'k': return 11;
        default:
            printf("No symbol for %c", symbol);
            exit(EXIT_FAILURE);
    }
}

void print_position(uint64_t position){
    // Determine the number of bits in an int64_t
    int numBits = sizeof(position) * 8;
    
    // Iterate through each bit from left to right
    for (int i = numBits - 1; i >= 0; i--) {
        // Check if the current bit is set
        if (position & ((uint64_t)1 << i))
            printf("1");
        else
            printf("0");

        if(i % 8 == 0){
            printf("\n");
        }
    }
    printf("\n");
}

Move get_move_from_user(){
    char* input = malloc(sizeof(char)* 100);
    printf("Enter a Move: ");
    scanf("%s", input);
    //printf("String is %d chars long.\n", strlen(input));
    
    // #TODO Optimise 100 character limit 
    char* origin = malloc(sizeof(char)* 100);
    char* destination = malloc(sizeof(char)* 100);
    
    if (strlen(input) == 4) {
        strncpy(origin, input, 2);
        origin[2] = '\0';  

        strncpy(destination, input + 2, 2);
        destination[2] = '\0';

        //printf("Origin: %s\n", origin);
        //printf("Destination: %s\n", destination);
    } else if(strlen(input) == 2){
        strncpy(origin, input, 2);
        origin[2] = '\0';
        
        printf("Enter a Destination square: ");
        scanf("%s", destination);
        //printf("Origin: %s\n", origin);
        //printf("Destination: %s\n", destination);
   
    }else{
        printf("Please enter a Move in the form of 'e2e4' or a select a piece with 'e2'\n   ");
    }
    return create_move(get_bitmap_from_notation(origin), get_bitmap_from_notation(destination)); 
        
    
}