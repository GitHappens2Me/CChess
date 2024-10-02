#pragma once


/*
 Compile with (Optimizations): 
    gcc -O3 -o CChess ./source_files/main.c ./source_files/board.c ./source_files/inout.c ./source_files/move.c ./source_files/notation.c ./source_files/engine.c
 Run with:
    ./CChess 
 Compile Tests with:
    gcc -o test ./tests/test.c ./source_files/board.c ./source_files/inout.c ./source_files/move.c ./source_files/notation.c
 Run Tests with:
     ./test
 Profile with:
    gcc -g -pg  -Wall -Wextra -o CChess ./source_files/main.c ./source_files/board.c ./source_files/inout.c ./source_files/move.c ./source_files/notation.c ./source_files/engine.c -no-pie
    & 
    -Run the executable-  ./CChess 
    &
    gprof ./CChess.exe gmon.out > analysis.txt 
 Check for MemLeaks (In Linux WSL)
    valgrind --leak-check=full ./CChess
 Debug with:
    gcc -g -pg  -Wall -Wextra -o CChess ./source_files/main.c ./source_files/board.c ./source_files/inout.c ./source_files/move.c ./source_files/notation.c ./source_files/engine.c
    &
    gdb ./CChess
 Static Code Analyser:
    gcc -g -pg  -Wall -Wextra -Wpedantic -o CChess ./source_files/main.c ./source_files/board.c ./source_files/inout.c ./source_files/move.c ./source_files/notation.c ./source_files/engine.c -no-pie -fanalyzer
 Generate Assembler Code
    gcc -S CChess.s ./source_files/main.c ./source_files/board.c ./source_files/inout.c ./source_files/move.c ./source_files/notation.c ./source_files/engine.c

    
*/

// Example Function Comment:
/*
 * computes an approximation of pi using:
 *    pi/6 = 1/2 + (1/2 x 3/4) 1/5 (1/2)^3  + (1/2 x 3/4 x 5/6) 1/7 (1/2)^5 +
 *
 *  n: number of terms in the series to sum
 *
 *  returns: the approximate value of pi obtained by suming the first n terms
 *           in the above series
 *           returns zero on error (if n is non-positive)
 * 
 *  notes: 
 * 
 *  TODO: 
 */


