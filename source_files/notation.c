#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../header_files/notation.h"


uint64_t get_bitmap_from_position(char* notation){
    if(strlen(notation) != 2){
        printf("Notation %s not valid!", notation);
        return 0;
    }

    printf("not: %s\n", notation);
    uint64_t position = 0x1;

    int collumn = tolower(notation[0]) - 97;
    printf("col: %d\n", collumn);

    int row = (notation[1] - '0') - 1;
    printf("row: %d\n", row);

    if(collumn < 0 || collumn > 7 || row < 0 || row > 7){
        printf("Notation %s not valid!", notation);
        return 0;
    }

    position = position << (7 - collumn);
    position = position << (8 * row);


    return position;
}