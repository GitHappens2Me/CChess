#pragma once

#include <assert.h>

#include "../header_files/board.h"
#include "../header_files/inout.h"

void test_split_bitmap(){
    uint64_t* indivdual_pieces = malloc(sizeof(uint64_t) * 64);

    // Full bitmap
    assert(split_bitmap(0xFFFFFFFFFFFFFFFFULL, indivdual_pieces) == 64);

    // Empty bitmap
    assert(split_bitmap(0ULL, indivdual_pieces) == 0);
    
    // Startpostion Bitmap
    assert(split_bitmap(0xFFFF00000000FFFFULL, indivdual_pieces) == 32);

    printf("Function 'test_split_bitmap' PASSED all tests.\n");
}

void test_initialize_board_FEN(){

    //#TODO find better way to test the initialization. Just comparing get_all_pieces(board) misses some errors that might occur

    Board* board;
    create_board(&board);

    char starting_pos[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    char ruy_lopez[] = "r1bqkb1r/pppp1ppp/2n2n2/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4";
    char queens_board[] = "QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ/QQQQQQQQ w - - 0 1";
    char random[] = "r1bqk2r/1ppp1ppp/8/pB6/1P2P1n1/3P4/P2N1PPP/b2QK2R w Kkq - 2 11";
    char en_passant_setup[] = "1nbqkbn1/r2ppppr/pp5p/7Q/2p1P3/2P3P1/PP1P1PBP/RNB1K1NR w KQ - 3 8";

    initialize_board_FEN(board, starting_pos);
    assert(get_all_pieces(board) == 0xFFFF00000000FFFF);

    initialize_board_FEN(board, ruy_lopez);
    assert(get_all_pieces(board) == 0xBDF724480804F7F9);

    initialize_board_FEN(board, queens_board);
    assert(get_all_pieces(board) == 0xFFFFFFFFFFFFFFFF);

    initialize_board_FEN(board, random);
    assert(get_all_pieces(board) == 0xB97700C04A109799);

    initialize_board_FEN(board, en_passant_setup);
    assert(get_all_pieces(board) == 0x7E9FC1012822D7EB);

    printf("Function 'test_initialize_board_FEN' PASSED all tests.\n");


}

void test_get_pieces_of_player(){
    Board* board;
    create_board(&board);
    initialize_board(board);

    assert(get_pieces_of_player(board, PLAYER_WHITE) == 0x000000000000FFFF);
    assert(get_pieces_of_player(board, PLAYER_BLACK) == 0xFFFF000000000000);

    char ruy_lopez[] = "r1bqkb1r/pppp1ppp/2n2n2/1B2p3/4P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4";
    initialize_board_FEN(board, ruy_lopez);

    assert(get_pieces_of_player(board, PLAYER_WHITE) == 0x000000400804F7F9);
    assert(get_pieces_of_player(board, PLAYER_BLACK) == 0xBDF7240800000000);


    printf("Function 'test_get_pieces_of_player' PASSED all tests.\n");

}



void test_generate_pseudolegal_moves_for_knight(){
    Board* board;
    create_board(&board);
    //initialize_board(board);
    Move* pseudo_legal_moves = malloc(sizeof(Move) * 64);

    // Knight on e4 on empty board
    uint64_t knight_position = get_bitmap_from_notation("e4");
    board->pieces[WHITE_KNIGHTS] = knight_position;
    assert(generate_pseudolegal_moves_for_knight(board, knight_position, PLAYER_WHITE, pseudo_legal_moves) == 8);

    // Knight on h1 on empty board
    knight_position = get_bitmap_from_notation("h1");
    board->pieces[WHITE_KNIGHTS] = knight_position;
    assert(generate_pseudolegal_moves_for_knight(board, knight_position, PLAYER_WHITE, pseudo_legal_moves) == 2);

    // Knight on a8 on empty board
    knight_position = get_bitmap_from_notation("a8");
    board->pieces[WHITE_KNIGHTS] = knight_position;
    assert(generate_pseudolegal_moves_for_knight(board, knight_position, PLAYER_WHITE, pseudo_legal_moves) == 2);

    // Knight on e4 with 4 Captures possible and 4 white pieces blocking
    knight_position = get_bitmap_from_notation("e4");
    board->pieces[WHITE_KNIGHTS] = knight_position;
    board->pieces[WHITE_ROOKS] = 0x0000000000221400;
    board->pieces[BLACK_ROOKS] = 0x0000142200000000;
    assert(generate_pseudolegal_moves_for_knight(board, knight_position, PLAYER_WHITE, pseudo_legal_moves) == 4);
    initialize_board_empty(board);


    printf("Function 'test_generate_pseudolegal_moves_for_knight' PASSED all tests.\n");

}

void test_generate_pseudolegal_moves_for_rook(){
    Board* board;
    create_board(&board);
    //initialize_board(board);
    Move* pseudo_legal_moves = malloc(sizeof(Move) * 64);

    // Knight on e4 on empty board
    uint64_t rook_position = get_bitmap_from_notation("e4");
    board->pieces[WHITE_ROOKS] = rook_position;
    assert(generate_pseudolegal_moves_for_rook(board, rook_position, PLAYER_WHITE, pseudo_legal_moves) == 14);

    // Rook on h1 on empty board
    rook_position = get_bitmap_from_notation("h1");
    board->pieces[WHITE_ROOKS] = rook_position;
    assert(generate_pseudolegal_moves_for_rook(board, rook_position, PLAYER_WHITE, pseudo_legal_moves) == 14);

    // Rook on a8 on empty board
    rook_position = get_bitmap_from_notation("a8");
    board->pieces[WHITE_ROOKS] = rook_position;
    assert(generate_pseudolegal_moves_for_rook(board, rook_position, PLAYER_WHITE, pseudo_legal_moves) == 14);

    // Rook on e4 with 4 Captures possible and 4 white pieces blocking
    rook_position = get_bitmap_from_notation("e4");
    board->pieces[WHITE_ROOKS] = rook_position;
    board->pieces[WHITE_KNIGHTS] = 0x0000000020000000;
    board->pieces[BLACK_ROOKS] =   0x0800000002080000;
    assert(generate_pseudolegal_moves_for_rook(board, rook_position, PLAYER_WHITE, pseudo_legal_moves) == 8);
    initialize_board_empty(board);


    printf("Function 'test_generate_pseudolegal_moves_for_rook' PASSED all tests.\n");

}

void test_perft(){

    Board* board;
    create_board(&board);
    //initialize_board(board);
    char fen_string[] = "rnb1k2r/2p1bppp/p2q1n2/3pN3/1p1K1P2/3P4/PPPBP1PP/RN1Q1B1R w kq - 2 9";
    initialize_board_FEN(board, fen_string);
    //apply_move(board, create_move(WHITE_KNIGHTS, get_bitmap_from_notation("e5"), get_bitmap_from_notation("d7"),0,0,0,0,0));
    //apply_move(board, create_move(BLACK_PAWNS, get_bitmap_from_notation("b7"), get_bitmap_from_notation("b5"),0,0,0,0,get_bitmap_from_notation("b6")));
    //apply_move(board, create_move(WHITE_KING, get_bitmap_from_notation("e1"), get_bitmap_from_notation("d2"),0,0,0,0,0));
    //apply_move(board, create_move(BLACK_PAWNS, get_bitmap_from_notation("b5"), get_bitmap_from_notation("b4"),0,0,0,0,0));
   

    print_board(board);

    int num_moves = 0;
    
    
    Board* board_copy;
    create_board(&board_copy);

    
    for(int i = 0; i < 10; i++){
        num_moves = perft(board_copy, i);
        printf("Perft(%d): %d\n", i, num_moves);
        copy_board(board_copy, board);
        //print_board(board_copy);
    }
    free_board(board_copy);
        
    //assert(perft(board, 1) == 20);
    //assert(perft(board, 2) == 400);
    //assert(perft(board, 3) == 8902);
    //assert(perft(board, 4) == 197281);
    assert(perft(board, 5) == 4865609);

    printf("Function 'test_perft' PASSED all tests.\n");

    free_board(board);
}

int perft(Board* board, int depth){

    

    Move move_list[256];
    int n_moves, i;
    uint64_t nodes = 0;

    if (depth == 0) return 1ULL;

    n_moves = generate_all_legal_moves_for_player(board, board->current_Player, move_list);
    
    Board* board_copy;
    create_board(&board_copy);
    for (i = 0; i < n_moves; i++) {

        copy_board(board_copy, board);
        apply_move_forced(board_copy, move_list[i]);
        nodes += perft(board_copy, depth - 1);
        if(depth == 10){
            print_move(move_list[i]);
            printf(" %d moves\n", perft(board_copy, depth - 1));
        }
    }
    return nodes;
    free_board(board_copy);
}

/*
(Tiefe): Mein Ergebnis : [Richtige Lösung]
(0): 1                 : [1]                 ✓
(1): 20                : [20]                ✓
(2): 400               : [400]               ✓ 
(3): 8,902             : [8,902]             ✓ // behobener fehler: En-Passant schlagen von spalte a nach h
(4): 197,281           : [197,281]           X // behobener fehler: Bauern konnten von Spalte a und h aus keine figuren schlagen 
(5): 4,865,609         : [4,865,609]         X // behobener fehler: Könige konnten in Schach von Bauern ziehen (is_attacked hat bauern nicht berücksichtigt)
(6): 119,186,762 (alt) : [119,060,324]       X
(7):                   : [3,195,901,860]     X


*/