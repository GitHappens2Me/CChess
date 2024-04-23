#include <stdlib.h>
#include <stdio.h>

#include "../header_files/board.h"
#include "../header_files/main.h"

int main(int argc, char *argv[]) {

    printf("Hello World!\n");

    Board* board;

    create_board(&board);

    initialize_board(board);

    print_board(board);

    printf("Bye Bye\n");
}
