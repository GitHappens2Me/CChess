
/*
 Compile with: 
    gcc -o test .\tests\test.c .\source_files\board.c .\source_files\inout.c .\source_files\move.c .\source_files\notation.c

 Run with:
    ./test
*/

#include <stdlib.h>
#include <assert.h>

#include "test_notation.c"

/*
#include "../header_files/board.h"
#include "../header_files/main.h"
#include "../header_files/inout.h"
#include "../header_files/move.h"
#include "../header_files/notation.h"
*/

int main(int argc, char *argv[]) {
    
    test_get_bitmap_from_notation();
    test_get_notation_from_bitmap();

}