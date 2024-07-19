
# Chess Engine

Welcome to the [CChess](https://github.com/GitHappens2Me/CChess) project! Here you can find the implementation of a simple chess engine written in pure C. The engine is designed to handle board representation, move generation, and basic game logic. It is a work in progress and many features are not yet implemented. 

## Table of Contents

- [Features](#features)
- [Installation & Usage](#installation-and-usage)
- [Development Progress](#development-progress)

## Features

- **Board Representation**: Efficiently represents the chess board using bitboards.
- **Move Generation**: Generates legal moves for all pieces, considering basic chess rules.
- **FEN Parsing**: Initializes the board from a FEN string.


## Installation and Usage

To build the project, you need to have a C compiler installed. Clone the repository and compile the source files using the following commands:

```bash
git clone https://github.com/GitHappens2Me/CChess.git
cd CChess

gcc -o CChess .\source_files\main.c .\source_files\board.c .\source_files\inout.c .\source_files\move.c .\source_files\notation.c
./CChess
```



---

## Development Progress

Please note that this project is still under development. Here are some planned features and improvements:

- [ ] **Complete Move Generation**: Handle all special moves (castling, en passant, pawn promotion).
- [ ] **Game Ending Detection**: Implement functions to detect all game-ending conditions. (Stalemate, 50 move Rule)
- [ ] **Board Evaluation**: Implement the evaluation function for move selection.
- [ ] **MiniMax Algorithm**: Implement the MiniMax Algorithm to select optimal Moves.
- [ ] **Performance Optimization**: Optimize the code for faster move generation and board evaluation.
- [ ] **Unit Tests**: Add comprehensive unit tests to ensure code quality and correctness.
- [ ] **Easier Compilation**: Implement a MakeFile, to work on Windows

Thank you for your interest in the Chess Engine project! If you have any questions or need assistance, feel free to open an issue or contact the maintainers. 
