#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../header_files/notation.h"
#include "../header_files/board.h"

/*
 *  returns the corresponding uint64_t bitmap to a given chess notation
 *  using the get_symbol_for_piecetype function to translate from piece_type to symbol
 *  e.g.  g3 -> 00000000
                00000000
                00000000
                00000000
                00000000
                00000010
                00000000
                00000000
 * 
 *  notation: chess notation as char*
 * 
 *  returns: corresponding bitmap as uint64_t
 */
uint64_t get_bitmap_from_position(char* notation){
    if(strlen(notation) != 2){
        printf("Notation %s not valid!\n", notation);
        return 0;
    }

    //printf("not: %s\n", notation);

    int column = tolower(notation[0]) - 'a';
    //printf("col: %d\n", column);

    int row = (notation[1] - '0') - 1;
    //printf("row: %d\n", row);

    if(column < 0 || column >= NUM_OF_COLLUMNS || row < 0 || row >= NUM_OF_ROWS){
        printf("Notation %s not valid!", notation);
        return 0;
    }
    /*
    position = position << (7 - column);
    position = position << (8 * row);*/

    uint64_t position = 1ULL << (NUM_OF_COLLUMNS * row + (7 - column));

    return position;
}