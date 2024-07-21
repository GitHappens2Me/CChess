#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "../header_files/board.h"
#include "../header_files/main.h"
#include "../header_files/inout.h"
#include "../header_files/move.h"
#include "../header_files/notation.h"
#include "../header_files/engine.h"



//TODO: use github Issues to track Progress

//#TODO rename Pseudo-legal / legal (maybe valid, allowed etc?)

int main() {

    printf("Hello World!\n");

    Board* board;

    create_board(&board);

    initialize_board(board);


    /*
    print_board(board);
    Move test_move = {0x100, 0x10000};
    apply_move(board, test_move);
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
    

/*
    uint64_t pos = 1;    
    for(int i = 0; i < 64; i++){
        
        uint64_t pslegalmoves = generate_pseudolegal_moves_for_piece(board, pos);

        if(pslegalmoves != 0){
            printf("Possible Moves from %s\n", get_notation_from_bitmap(pos));
            print_position(pslegalmoves);
        }
        pos = pos << 1;
    }
*/
    // Test split_bitmap

    uint64_t* indivdual_pieces = malloc(sizeof(uint64_t) * 64);
    int count = split_bitmap(get_all_pieces(board), indivdual_pieces);
    printf("Number of Pieces in Position: %d\n",count);
    //print_position(indivdual_pieces[1]);
    //for(int i = 0; i < count; i++){
    //    print_position(indivdual_pieces[i]);
    //}
    free(indivdual_pieces);
    
    // Test initializing from FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    Board* fen_board;

    create_board(&fen_board);
    //char fen_String[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; // Using a writable buffer
    char fen_String[] = "r4bnr/ppp1kppp/2n5/3qp3/2B3b1/3P1N2/PPP1QPPP/RNB1K2R w KQ - 3 7";
    
    initialize_board_FEN(fen_board, fen_String);

    printf("Fenboard:\n");
    print_board(fen_board);
    free_board(fen_board);    

    // Test copying Board:

    Board* board_copy;
    create_board(&board_copy);
    copy_board(board_copy, board);

    Move e2e4 = {get_bitmap_from_notation("e2"), get_bitmap_from_notation("e4")};

    apply_move(board_copy, e2e4);

    printf("Original\n:");
    print_board(board);
    printf("Copy\n:");
    print_board(board_copy);

    free_board(board_copy);
 


    
    Move* legal_moves = malloc(sizeof(Move) * 200);

    // Test by Playing: 

    printf("\n\n\n\nStarting Game\n");
    int num_legal_moves = generate_all_legal_moves_for_player(board, board->current_Player, legal_moves);
    printf("Legal Moves = %d\n", num_legal_moves);
    
    printf("Simple Evaluation: %f\n", evaluate(board));
    printf("Best Move: ");
    free(legal_moves);

    
    Move move;

/*
    printf("%d: ",get_best_move(board, &move, 0, 1));
    print_move(move);
*/
    int engine_move = 1;
    
    print_board(board);

    while (1) {
        if(engine_move){
            if(board->current_Player == 1){
                //get_best_move(board, &move, 0, 3);
                get_best_move_minimax(board, &move, 5);
                printf("Engine Move: ");
                print_move(move);
            }else{
                move = get_move_from_user();
            }
        }else{
            move = get_move_from_user();
        }

        if(apply_move(board, move) == 1){
            printf("Applied: ");
            print_move(move);
            Move* legal_moves = malloc(sizeof(Move) * 200);
            num_legal_moves = generate_all_legal_moves_for_player(board, board->current_Player, legal_moves);
            printf("Simple Evaluation: %f\n", evaluate(board));
            free(legal_moves);

            /*
            printf("Best Move: ");
            
            printf("%d: ",get_best_move(board, &move, 0,2));

            print_move(move);
*/
            if(num_legal_moves == 0){
                printf("Player %d is Checkmate\n", board->current_Player);
            }else{
                printf("Player %d has %d Legal Moves.\n", board->current_Player, num_legal_moves);
            }

            print_board(board);
            printf("Current Player: %d\n", board->current_Player);

            if(is_attacked(board, move.destination, board->current_Player)){
                printf("The Destination Square is attacked\n");
            }else{
                printf("Not Attacked\n");
            }
            if(is_in_check(board, PLAYER_WHITE)) printf("White is in Check");
            if(is_in_check(board, PLAYER_BLACK)) printf("Black is in Check");
            
        }





    }


    // Test by showing posible Moves for specified Piece
    while (1) {
        char* input = malloc(sizeof(char) * 100);
        printf("Enter a position ");
        scanf("%s", input);
        

        print_position(generate_pseudolegal_moves_for_piece(board, get_bitmap_from_notation(input)));

    }
    printf("Bye Bye\n");
    
}
