#include <stdlib.h>
#include <stdio.h>

#include "../header_files/board.h"
#include "../header_files/main.h"

int main(int argc, char *argv[]) {

    printf("Hello World!\n");

    Board* board;

    create_board(&board);

    initialize_board(board);

    //print_board(board);
    
    /*
    printf("\n");
    for (int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        printf("%d:\n", i);
        print_pieces(board, i);
        printf("\n");
    
    }
    printf("Bye Bye\n");
    */
}
