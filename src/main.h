/*
Author: Michael Bopp
Filename: main.h
Description:
Date Created: 07/05/23
Last Modified: 08/01/23
*/

#ifndef MAIN_H
#define MAIN_H
#include "board.h"

// Initialize the terminal settings
void initTerminal();

// Calculate the offsets for the chess board
std::pair<int, int> calculateOffsets();

// Set up the pieces on the chess board
void setupPieces(ChessBoard& chessBoard);

// Handle the mouse click events
void handleMouseClick(ChessBoard& chessBoard, MEVENT& event, int offsetX, int offsetY);

// The main game loop
bool gameLoop(ChessBoard& chessBoard, MEVENT& event, int offsetX, int offsetY);

#endif //MAIN_H