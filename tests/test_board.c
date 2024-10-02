#pragma once

#include <assert.h>
#include <time.h>
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

    free(indivdual_pieces);

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

    free_board(board);

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

    free_board(board);

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

    free_board(board);
    free(pseudo_legal_moves);

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

    free_board(board);
    free(pseudo_legal_moves);


    printf("Function 'test_generate_pseudolegal_moves_for_rook' PASSED all tests.\n");

}

void test_unmake_move(){

}




#define DEBUGDEPTH 6
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
        if(depth == DEBUGDEPTH){
            print_move(move_list[i]);
            printf(" %d moves\n", perft(board_copy, depth - 1));
        }
    }
    free_board(board_copy);
    return nodes;
}

int perft_with_unmake(Board* board, int depth){

    Move move_list[256];
    int n_moves, i;
    uint64_t nodes = 0;

    if (depth == 0) return 1ULL;

    n_moves = generate_all_legal_moves_for_player(board, board->current_Player, move_list);
    

    for (i = 0; i < n_moves; i++) {

        // store unreversable board info
        uint8_t old_castling_rights = board->castling_rights;
        uint64_t old_en_passant_square = board->en_passant_square;

        apply_move_forced(board, move_list[i]);
        nodes += perft_with_unmake(board, depth - 1);
        if(depth == DEBUGDEPTH){
            print_move(move_list[i]);
            printf(" %d moves\n", perft_with_unmake(board, depth - 1));
        }
        unmake_move(board, move_list[i], old_en_passant_square, old_castling_rights);

    }

    return nodes;
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






void test_perft(){

    Board* board;
    create_board(&board);
    
    printf("Starting Perft-Test: ");
    clock_t begin = clock();

    initialize_board(board);
    assert(perft(board, 4) == 197281);
    //assert(perft(board, 5) == 4865609 );
    //assert(perft_with_unmake(board, 4) == 197281);
    //assert(perft_with_unmake(board, 5) == 4865609 );

    char kiwipete[] = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ";
    initialize_board_FEN(board, kiwipete);
    board->castling_rights = 0xF; // FEN initialzation does not recognize Castling rights yet
    //assert(perft(board, 4) == 4085603);    
    //assert(perft(board, 5) == 193690690 );
    assert(perft_with_unmake(board, 4) == 4085603);    
    //assert(perft_with_unmake(board, 5) == 193690690 );

    char rook_endgame[] = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ";
    initialize_board_FEN(board, rook_endgame);
    board->castling_rights = 0x0; // FEN initialzation does not recognize Castling rights yet
    //assert(perft(board, 4) == 43238);  
    //assert(perft(board, 5) == 674624);
    assert(perft_with_unmake(board, 4) == 43238);  
    //assert(perft_with_unmake(board, 5) == 674624);

    char middle_game[] = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
    initialize_board_FEN(board, middle_game);
    board->castling_rights = 0xC; // FEN initialzation does not recognize Castling rights yet
    //assert(perft(board, 4) == 422333);
    //assert(perft(board, 5) ==  15833292); 
    assert(perft_with_unmake(board, 4) == 422333);
    //assert(perft_with_unmake(board, 5) ==  15833292); 

    char difficult_pos[] = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8 ";
    initialize_board_FEN(board, difficult_pos);
    board->castling_rights = 0x3; // FEN initialzation does not recognize Castling rights yet
    //assert(perft(board, 4) == 2103487);  
    //assert(perft(board, 5) ==  89941194); 
    assert(perft_with_unmake(board, 4) == 2103487);  
    //assert(perft_with_unmake(board, 5) ==  89941194); 

    char alternative[] = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
    initialize_board_FEN(board, alternative);
    board->castling_rights = 0x0; // FEN initialzation does not recognize Castling rights yet
    //assert(perft(board, 4) == 3894594); 
    //assert(perft(board, 5) ==  164075551); 
    assert(perft_with_unmake(board, 4) == 3894594); 
    //assert(perft_with_unmake(board, 5) ==  164075551); 

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Function 'test_perft' PASSED all tests in %lf Seconds.\n", time_spent);

    free_board(board);
}
