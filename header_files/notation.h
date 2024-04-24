#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

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
uint64_t get_bitmap_from_position(char* notation);