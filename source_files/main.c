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
    printf("Black's Pieces:");
    print_position(get_pieces_of_player(board, PLAYER_BLACK));

    printf("Piecetypeindex: %d\n", get_piece_type_at(board, get_bitmap_from_notation("a8")));

    //print_position(COLLUMN_a);
    //print_position(ROW_1);

    print_position(generate_pseudolegal_moves_for_rook(board, get_bitmap_from_notation("g4"), PLAYER_BLACK));
    print_position(generate_pseudolegal_moves_for_bishop(board, get_bitmap_from_notation("g4"), PLAYER_BLACK));

    printf("a5\n");
    print_position(generate_pseudolegal_moves_for_knight(board, get_bitmap_from_notation("a6"), PLAYER_WHITE));
    

    while (1) {
        char input[100];
        printf("Enter a position ");
        scanf("%s", &input);
        
        print_position(generate_pseudolegal_moves_for_pawn(board, get_bitmap_from_notation(input), PLAYER_BLACK));

    }
    printf("Bye Bye\n");
    
}
