# Command: gcc -o main .\source_files\main.c .\source_files\board.c .\source_files\inout.c .\source_files\move.c .\source_files\notation.c 

# Define compiler: gcc
CC=gcc

# Definde compiler-flags: -WALL (show all Warnings)
CFLAGS=WALL

# Define Source-Directory
SRCDIR=source_files

# all-target is the default target, when no other target is specified
all:
	main


main:	$(wildcard  $(SRCDIR)/*.c)
	$(CC)  $(CFLAGS)  -o main  $^


clean:
    rm -f main

.PHONY: all clean