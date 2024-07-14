#pragma once

#include <assert.h>

#include "../header_files/notation.h"
#include "../header_files/inout.h"

void test_get_bitmap_from_notation(){

    // Empty notation string
    assert(get_bitmap_from_notation("") == 0);
    assert(get_bitmap_from_notation(" ") == 0);
    assert(get_bitmap_from_notation("  ") == 0);

    // Invalid length notation strings
    assert(get_bitmap_from_notation("a") == 0);
    assert(get_bitmap_from_notation("a1b") == 0);
    assert(get_bitmap_from_notation("a10") == 0);

    // Invalid column characters
    assert(get_bitmap_from_notation("i1") == 0);
    assert(get_bitmap_from_notation("j3") == 0);
    assert(get_bitmap_from_notation("z5") == 0);

    // Invalid row characters
    assert(get_bitmap_from_notation("a0") == 0);
    assert(get_bitmap_from_notation("b9") == 0);
    assert(get_bitmap_from_notation("h10") == 0);

    // Valid notations
    assert(get_bitmap_from_notation("a1") == 1ULL << 7);  // 00000000 00000000 ... 10000000 (position 7)
    assert(get_bitmap_from_notation("h1") == 1ULL << 0);  // 00000000 00000000 ... 00000001 (position 0)
    assert(get_bitmap_from_notation("a8") == 1ULL << 63);   // 10000000 ... 00000000 (position 63)
    assert(get_bitmap_from_notation("h8") == 1ULL << 56);   // 00000001 ... 00000000 (position 56)
    assert(get_bitmap_from_notation("d4") == 1ULL << 28);  // (position 28)
    assert(get_bitmap_from_notation("e5") == 1ULL << 35);  // (position 35)

    // Valid uppercase notations
    assert(get_bitmap_from_notation("A1") == 1ULL << 7);
    assert(get_bitmap_from_notation("H1") == 1ULL << 0);
    assert(get_bitmap_from_notation("E5") == 1ULL << 35);

    // Test whitespace around input
    assert(get_bitmap_from_notation(" a1") == 0);
    assert(get_bitmap_from_notation("h1 ") == 0);
    assert(get_bitmap_from_notation(" a8 ") == 0);

    printf("Function 'get_bitmap_from_notation' PASSED all tests.\n");

}

void test_get_notation_from_bitmap() {
    
    // Zero bitmap (no bits set)
    assert(strcmp(get_notation_from_bitmap(0), "") == 0);

    // Valid bitmaps
    assert(strcmp(get_notation_from_bitmap(1ULL << 7), "a1") == 0);    // 00000000 00000000 ... 10000000 (position 7)
    assert(strcmp(get_notation_from_bitmap(1ULL << 0), "h1") == 0);    // 00000000 00000000 ... 00000001 (position 0)
    assert(strcmp(get_notation_from_bitmap(1ULL << 63), "a8") == 0);   // 10000000 ... 00000000 (position 63)
    assert(strcmp(get_notation_from_bitmap(1ULL << 56), "h8") == 0);   // 00000001 ... 00000000 (position 56)
    assert(strcmp(get_notation_from_bitmap(1ULL << 28), "d4") == 0);  
    assert(strcmp(get_notation_from_bitmap(1ULL << 35), "e5") == 0); 

    // Bitmaps with multiple set bits #TODO Those tests dont work. get_notation_from_bitmap should return int and place the calculated notation in a parameter
    assert(strcmp(get_notation_from_bitmap(1111ULL), "a1") == 0);  
    assert(strcmp(get_notation_from_bitmap(100001ULL), "h1") == 0);   
    assert(strcmp(get_notation_from_bitmap(01010ULL), "a8") == 0);   


    // Free allocated memory
    free(get_notation_from_bitmap(1ULL << 7));
    free(get_notation_from_bitmap(1ULL << 0));
    free(get_notation_from_bitmap(1ULL << 63));
    free(get_notation_from_bitmap(1ULL << 56));
    free(get_notation_from_bitmap(1ULL << 28));
    free(get_notation_from_bitmap(1ULL << 35));
    free(get_notation_from_bitmap(1ULL << 0));
    free(get_notation_from_bitmap(1ULL << 63));
    free(get_notation_from_bitmap(1ULL << 62));
    free(get_notation_from_bitmap(1ULL << 1));

    printf("Function 'get_notation_from_bitmap' PASSED all tests.\n");
}