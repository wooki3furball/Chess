/*
Author: Michael Bopp
Filename: board.h
Description:
Date Created: 07/05/23
Last Modified: 08/01/23
*/

#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"

#define RANK_SIZE 8 // Row in Chess
#define FILE_SIZE 8 // Column in Chess

class ChessBoard {
public:
    static bool notation_mode;
    ChessPiece* selectedPiece;
    int selectedX, selectedY;
    int selectedFile, selectedRank;

    ChessPiece* getPieceAt(int x, int y);
    void setPieceAt(ChessPiece* piece, int x, int y);
    ChessBoard(int offsetX, int offsetY);
    void drawBoard();
    void placePiece(ChessPiece* piece, int x, int y);
    void movePiece(int fromX, int fromY, int toX, int toY);

    int getOffsetX() const;
    int getOffsetY() const;
    ~ChessBoard();

private:
    ChessPiece* grid[RANK_SIZE][FILE_SIZE];
    int offsetX, offsetY;
    ChessPiece* pieces[RANK_SIZE][FILE_SIZE];  // Holds the current state of the board.
};

void drawClock(int x, int y);

void drawExit(int x, int y);

#endif //BOARD_H