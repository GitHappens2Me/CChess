#pragma once

#include <assert.h>

#include "../header_files/board.h"
#include "../header_files/inout.h"

#define EMPTY_BOARD {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void test_split_bitmap(){
    uint64_t indivdual_pieces[] = EMPTY_BOARD;

    // Empty bitmap
    assert(split_bitmap(0ULL, indivdual_pieces) == 0);

    // Full bitmap
    assert(split_bitmap(0xFFFFFFFFFFFFFFFFULL, indivdual_pieces) == 64);

    // Startpostion Bitmap
    assert(split_bitmap(0xFFFF00000000FFFFULL, indivdual_pieces) == 32);

    
    printf("Function 'test_split_bitmap' PASSED all tests.\n");

}