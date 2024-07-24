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

    initialize_board_FEN(board, starting_pos);
    assert(get_all_pieces(board) == 0xFFFF00000000FFFF);

    initialize_board_FEN(board, ruy_lopez);
    assert(get_all_pieces(board) == 0xBDF724480804F7F9);

    initialize_board_FEN(board, queens_board);
    assert(get_all_pieces(board) == 0xFFFFFFFFFFFFFFFF);

    initialize_board_FEN(board, random);
    assert(get_all_pieces(board) == 0xB97700C04A109799);

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


    printf("Function 'test_initialize_board_FEN' PASSED all tests.\n");

}