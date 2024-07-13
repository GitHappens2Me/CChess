#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "../header_files/board.h"
#include "../header_files/main.h"
#include "../header_files/inout.h"
#include "../header_files/move.h"
#include "../header_files/notation.h"


//TODO: use github Issues to track Progress

int main(int argc, char *argv[]) {

    printf("Hello World!\n");

    Board* board;

    create_board(&board);

    initialize_board(board);


    /*
    print_board(board);
    Move test_move = {0x100, 0x10000};
    apply_move(board, test_move, FORCED);
    printf("After h3");
    print_board(board);
    */
    /*

    printf("\n");
    for (int i = 0; i < NUM_OF_PIECE_TYPES; i++){
        printf("%d:\n", i);
        print_pieces(board, i);
        printf("\n");
    
    }*/
    printf("Black's Pieces:\n");
    print_position(get_pieces_of_player(board, PLAYER_BLACK));

    printf("Piecetypeindex: %d\n\n", get_piece_type_at(board, get_bitmap_from_notation("a8")));

    //print_position(COLLUMN_a);
    //print_position(ROW_1);

    print_position(generate_pseudolegal_moves_for_rook(board, get_bitmap_from_notation("g4"), PLAYER_BLACK));
    print_position(generate_pseudolegal_moves_for_bishop(board, get_bitmap_from_notation("g4"), PLAYER_BLACK));

    printf("a5\n");
    print_position(generate_pseudolegal_moves_for_knight(board, get_bitmap_from_notation("a6"), PLAYER_WHITE));
    


    uint64_t pos = 1;    
    for(int i = 0; i < 64; i++){
        
        uint64_t pslegalmoves = generate_pseudolegal_moves_for_piece(board, pos);

        if(pslegalmoves != 0){
            printf("Possible Moves from %s\n", get_notation_from_bitmap(pos));
            print_position(pslegalmoves);
        }
        pos = pos << 1;
    }


    // Test by Playing: 
    print_board(board);
    while (1) {
        Move move = get_move_from_user();
        
        
        if(apply_move(board, move, UNFORCED) == 1){
            print_move(move);
            print_board(board);
            printf("Current Player: %d\n", board->current_Player);

            if(is_attacked(board, move.destination, board->current_Player)){
                printf("The Destination Square is attacked\n");
            }else{
                printf("Not Attacked\n");
            }

        }





    }

    // Test by showing posible Moves for specified Piece
    while (1) {
        char input[100];
        printf("Enter a position ");
        scanf("%s", &input);
        

        print_position(generate_pseudolegal_moves_for_piece(board, get_bitmap_from_notation(input)));

    }
    printf("Bye Bye\n");
    
}
