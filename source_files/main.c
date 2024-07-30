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


    Board* board;
    create_board(&board);
    initialize_board(board);

    // tests if user can capture en-passant (First move g1h2)
    //char en_passant_setup[] = "1k6/3Rp3/8/3P4/8/8/8/R1R3QK w - - 0 1";
    //initialize_board_FEN(board, en_passant_setup);

    // tests if engine can capture en-passant
    //char en_passant_setup2[] = "k7/8/8/8/3p4/8/4P3/K7 w - - 0 1";
    //initialize_board_FEN(board, en_passant_setup2);

    //char fen[] = "8/8/3r1r2/2r3r1/4N3/2R3R1/3R1R2/8 w - - 0 1";
    //initialize_board_FEN(board, fen);

    char promotion_test1[] = "k1r5/3P4/8/8/8/8/PP1p4/K7 w - - 0 1";
    initialize_board_FEN(board, promotion_test1);

    //char promotion_test2[] = "k7/8/8/8/8/8/PP1p4/K4Q2 w - - 0 1";
    //initialize_board_FEN(board, promotion_test2);
    // Test by Playing: 
    printf("Starting Game :)\n");

    int engine_move = 1;

    Move* legal_moves = malloc(sizeof(Move) * 200);
    int num_legal_moves = 0;
    Move move;


    print_board(board);

    while (1) {
        if(engine_move && board->current_Player == PLAYER_BLACK){
            get_best_move_minimax(board, &move, 4);
            printf("Engine Move: ");
            print_move(move);

            //exit(EXIT_SUCCESS); //Profiling
        }else{
            move = get_move_from_user(board);
            if(get_piece_color(board, move.moving_piece_origin) != board->current_Player){
                printf("Not your Piece. Choose a different Move\n");
                continue;
            }
        }

        if(apply_move(board, move) == 1){
            printf("Applied Move: ");
            print_move(move);
            printf("Captured piece: %d\n", move.captured_piece_type);

            num_legal_moves = generate_all_legal_moves_for_player(board, board->current_Player, legal_moves);
            printf("Simple Evaluation: %4.2f\n", ((float)evaluate(board) / 100));


            /*
            printf("WHITE\n");
            print_position(get_pieces_of_player(board, PLAYER_WHITE));
            printf("BLACK\n");
            print_position(get_pieces_of_player(board, PLAYER_BLACK));
            printf("EMPTY\n");
            print_position(board->pieces[0]);
            */
            
            print_board(board);


            
            if(num_legal_moves == 0){
                printf("Player %d is Checkmate\n", board->current_Player);
                exit(EXIT_SUCCESS);
            }else{
                printf("Player %d has %d Legal Moves.\n", board->current_Player, num_legal_moves);
            }
            if(is_in_check(board, PLAYER_WHITE)) printf("White is in Check");
            if(is_in_check(board, PLAYER_BLACK)) printf("Black is in Check"); 
            


            printf("Current Player: %d\n", board->current_Player);

            
        }
    }
}
