#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "../header_files/board.h"
#include "../header_files/main.h"
#include "../header_files/inout.h"
#include "../header_files/move.h"
#include "../header_files/notation.h"

int main(int argc, char *argv[]) {

    printf("Hello World!\n");

    Board* board;

    create_board(&board);

    initialize_board(board);

    print_board(board);
    
    Move test = {0x100, 0x10000, 0};

    apply_move(board, test);
    
    print_board(board);

    /*

    printf("\n");
    for (int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        printf("%d:\n", i);
        print_pieces(board, i);
        printf("\n");
    
    }*/


    while (1) {
        char input[100];
        printf("Enter a position ");
        scanf("%s", &input);
        /*
        if(get_bitmap_from_notation(input)){
            print_position(get_bitmap_from_notation(input));
        }*/
        if(get_bitmap_from_notation(input)){
            print_position(rook_move_vector(get_bitmap_from_notation(input)));
        }
    }
    printf("Bye Bye\n");
    
}
