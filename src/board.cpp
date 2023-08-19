/*
Author: Michael Bopp
Filename: board.cpp
Description:
Date Created: 07/05/23
Last Modified: 08/01/23
*/

#include "board.h"

bool ChessBoard::notation_mode = false;

ChessPiece* ChessBoard::getPieceAt(int x, int y) { 
    return pieces[y][x]; 
}

void ChessBoard::setPieceAt(ChessPiece* piece, int x, int y) {
    pieces[y][x] = piece;
}

ChessBoard::ChessBoard(int offsetX, int offsetY) : selectedFile(-1), selectedRank(-1), offsetX(offsetX), offsetY(offsetY) {
    for (int i = 0; i < RANK_SIZE; i++) {
        for (int j = 0; j < FILE_SIZE; j++) {
            pieces[i][j] = nullptr;  // Initialize empty board.
        }
    }
}

/* Fill the board with bullet points, & redraw pieces. */
void ChessBoard::drawBoard() {

    clear();

    if (notation_mode) { // check if notation mode is turned on
    for (int i = 0; i < RANK_SIZE; i++) // Draw row labels
        mvwprintw(stdscr, offsetY + i, offsetX - 2, "%d", 8 - i);
    for (int i = 0; i < FILE_SIZE; i++) // Draw column labels 
        mvwaddch(stdscr, offsetY + 8, offsetX + i*4 + 1, 'a' + i);
    }

    for (int i = 0; i < RANK_SIZE; i++) {
        for (int j = 0; j < FILE_SIZE; j++) {
            if ((i + j) % 2 == 0) {
                attron(COLOR_PAIR(2));
            } else {
                attron(COLOR_PAIR(1));
            }
            mvwaddwstr(stdscr, offsetY + i, offsetX + j*4, L" • ");
            attroff(COLOR_PAIR(1));
            attroff(COLOR_PAIR(2));
        }
    }

    for (int i = 0; i < RANK_SIZE; i++) {
        for (int j = 0; j < FILE_SIZE; j++) {
            if (pieces[i][j] != nullptr) {
                placePiece(pieces[i][j], j, i);
            }
        }
    }
}

void ChessBoard::placePiece(ChessPiece* piece, int x, int y) {
pieces[y][x] = piece;
    if (piece != nullptr) {  // check if the piece is not a nullptr
    mvwaddwstr(stdscr, offsetY + y, offsetX + x*4, piece->getSymbol()); // Use -> to access member functions of a pointer
    }
}   

void ChessBoard::movePiece(int fromX, int fromY, int toX, int toY) {
    // Check if the source cell is not empty
    if (pieces[fromY][fromX] == nullptr) {
        // Add error handling code here...
        return;
    }
    // Check if the destination cell is either empty or contains a piece of the opposite color
    if (pieces[toY][toX] != nullptr && pieces[toY][toX]->getColor() == pieces[fromY][fromX]->getColor()) {
        // Add error handling code here...
        return;
    }

    // Move the piece
    delete pieces[toY][toX];
    pieces[toY][toX] = pieces[fromY][fromX];
    pieces[fromY][fromX] = nullptr;

    // Redraw the board
    drawBoard();
}

int ChessBoard::getOffsetX() const {
    return offsetX; 
}

int ChessBoard::getOffsetY() const { 
    return offsetY; 
}

ChessBoard::~ChessBoard() {
    for (int i = 0; i < RANK_SIZE; ++i) {
        for (int j = 0; j < FILE_SIZE; ++j) {
            delete grid[i][j];  // Delete the piece if it exists.
            grid[i][j] = nullptr;  // Set the pointer to nullptr just to be safe.
        }
    }
}

void drawClock(int x, int y) {
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    mvwprintw(stdscr, y, x, "Current Time: %s", asctime(timeinfo));
}

void drawExit(int x, int y) {
    mvprintw(y, x, "[Exit]");
}