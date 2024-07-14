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
uint64_t get_bitmap_from_notation(char* notation){
    if(strlen(notation) != 2){
        //printf("Notation %s not valid!\n", notation);
        return 0;
    }

    //printf("not: %s\n", notation);

    int column = tolower(notation[0]) - 'a';    // 0 - 7
    //printf("col: %d\n", column);

    int row = (notation[1] - '0') - 1;      // 0 - 7
    //printf("row: %d\n", row);

    if(column < 0 || column >= NUM_OF_COLLUMNS || row < 0 || row >= NUM_OF_ROWS){
        //printf("Notation '%s' not valid!", notation);
        return 0;
    }

    // bitshift 1ULL (0x..001) to correct position
    uint64_t position = 1ULL << (NUM_OF_COLLUMNS * row + (7 - column));

    return position;
}


/*
 *  Returns the corresponding chess notation from a given uint64_t bitmap.
 *  Bitmap: uint64_t bitmap representing the position of a piece.
 *  Returns: corresponding chess notation as char*
 * 
 *  note: 
 *      #TODO maybe "void get_notation_from_bitmap(uint64_t bitmap, char* notation)" is better as i dont need to worry about memory management 
 *      #TODO check if bitmap contains only and atleast 1 set bit
 */
char* get_notation_from_bitmap(uint64_t bitmap) {
    char* notation = (char*)malloc(3 * sizeof(char));
    int row = 0, column = 0;

    // Find the row and column of the set bit (1)
    for (int i = 0; i < 64; ++i) {
        if (bitmap & (1ULL << i)) {
            row = i / NUM_OF_ROWS;
            column = i % NUM_OF_COLLUMNS;
            break;
        }
    }

    // Convert row and column to chess notation
    notation[0] = 'h' - column;
    notation[1] = '1' + row;
    notation[2] = '\0'; // Null-terminate the string

    return notation;
}