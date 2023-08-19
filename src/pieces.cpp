/*
Author: Michael Bopp
Filename: pieces.cpp
Description:
Date Created: 07/05/23
Last Modified: 08/01/23
*/

#include "pieces.h"

bool ChessPiece::ascii_mode = false;

/* Constructor */
ChessPiece::ChessPiece(Color color) : color(color) {}

const wchar_t* ChessPiece::getSymbol() {
    if (ascii_mode) {
        return getASCIISymbol();
    } else return getUnicodeSymbol();
}

Color ChessPiece::getColor() const {
    return color;
}

void ChessPiece::setColor(Color newColor) {
    color = newColor;
}

/* Default behaviour for the move and capture methods */
void ChessPiece::move(int eventY, int eventX, int& y, int& x, int boardHeight) {
    throw std::logic_error("Not implemented");
}

void ChessPiece::capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win) {
    throw std::logic_error("Not implemented");
}

/* Implementations of King's methods. */
King::King(Color color) : ChessPiece(color) {}

void King::move(int eventY, int eventX, int& y, int& x, int boardHeight) {
        if (abs(eventY - y) <= 1 && abs(eventX - x) <= 1) { 
            y = eventY;
            x = eventX;
        }
    }

void King::capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win) {
    if ((abs(eventY - y) <= 1 && abs(eventX - x) <= 1) && (eventX == capturedPieceX && eventY == capturedPieceY)) {
        y = eventY;
        x = eventX;
        capturedPieceX = capturedPieceY = -1; 
        wclear(message_win);
        wprintw(message_win, "Piece captured!");
        wrefresh(message_win);
        sleep(2); 
    }
}
 const wchar_t* King::getUnicodeSymbol() { return color == WHITE ? L" ♔ " : L" ♚ "; }
 const wchar_t* King::getASCIISymbol() { return color == WHITE ? L" K " : L" k "; }

/* Implementations of Queen's methods. */
Queen::Queen(Color color) : ChessPiece(color) {}

void Queen::move(int eventY, int eventX, int& y, int& x, int boardHeight) {
    int dy = eventY - y;
    int dx = eventX - x;
    if (dx != 0 && (dy/dx == 1 || dy/dx == -1)) {
        y = eventY;
        x = eventX;
    } else if (dx == 0 || dy == 0) {
        y = eventY;
        x = eventX;
    }
}
void Queen::capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win) {
    if ((abs(eventY - y) == abs(eventX - x) || eventX == x || eventY == y) && (eventX == capturedPieceX && eventY == capturedPieceY)) {
        y = eventY;
        x = eventX;
        capturedPieceX = capturedPieceY = -1;
        wclear(message_win);
        wprintw(message_win, "Piece captured!");
        wrefresh(message_win);
        sleep(2);
    }
}
 const wchar_t* Queen::getUnicodeSymbol() { return color == WHITE ? L" ♕ " : L" ♛ "; }
 const wchar_t* Queen::getASCIISymbol() { return color == WHITE ? L" Q " : L" q "; }

/* Implementations of Rook's methods. */
Rook::Rook(Color color) : ChessPiece(color) {}

void Rook::move(int eventY, int eventX, int& y, int& x, int boardHeight) {
    if (eventY == y || eventX == x) {
        y = eventY;
        x = eventX;
    }
}
void Rook::capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win) {
    if ((eventY == y || eventX == x) && (eventX == capturedPieceX && eventY == capturedPieceY)) {
        y = eventY;
        x = eventX;
        capturedPieceX = capturedPieceY = -1;
        wclear(message_win);
        wprintw(message_win, "Piece captured!");
        wrefresh(message_win);
        sleep(2);
    }
}
 const wchar_t* Rook::getUnicodeSymbol() { return color == WHITE ? L" ♖ " : L" ♜ "; }
 const wchar_t* Rook::getASCIISymbol() { return color == WHITE ? L" R " : L" r "; }

/* Implementations of Bishop's methods. */
Bishop::Bishop(Color color) : ChessPiece(color) {}

void Bishop::move(int eventY, int eventX, int& y, int& x, int boardHeight) {
    int dy = eventY - y;
    int dx = eventX - x;
    if (dx != 0 && (dy/dx == 1 || dy/dx == -1)) {
        y = eventY;
        x = eventX;
    }
}
void Bishop::capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win) {
    if ((abs(eventY - y) == abs(eventX - x)) && (eventX == capturedPieceX && eventY == capturedPieceY)) {
        y = eventY;
        x = eventX;
        capturedPieceX = capturedPieceY = -1;
        wclear(message_win);
        wprintw(message_win, "Piece captured!");
        wrefresh(message_win);
        sleep(2);
    }
}
 const wchar_t* Bishop::getUnicodeSymbol() { return color == WHITE ? L" ♗ " : L" ♝ "; }
 const wchar_t* Bishop::getASCIISymbol() { return color == WHITE ? L" B " : L" b "; }

/* Implementations of Knight's methods. */
Knight::Knight(Color color) : ChessPiece(color) {}

void Knight::move(int eventY, int eventX, int& y, int& x, int boardHeight) {
    int dy = abs(eventY - y);
    int dx = abs(eventX - x);
    if ((dy == 2 && dx == 1) || (dy == 1 && dx == 2)) {
        y = eventY;
        x = eventX;
    }
}
void Knight::capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win) {
    int dy = abs(eventY - y);
    int dx = abs(eventX - x);
    if (((dy == 2 && dx == 1) || (dy == 1 && dx == 2)) && (eventX == capturedPieceX && eventY == capturedPieceY)) {
        y = eventY;
        x = eventX;
        capturedPieceX = capturedPieceY = -1;
        wclear(message_win);
        wprintw(message_win, "Piece captured!");
        wrefresh(message_win);
        sleep(2);
    }
}
 const wchar_t* Knight::getUnicodeSymbol() { return color == WHITE ? L" ♘ " : L" ♞ "; }
 const wchar_t* Knight::getASCIISymbol() { return color == WHITE ? L" N " : L" n "; }

/* Implementations of Pawn's methods. */
Pawn::Pawn(Color color) : ChessPiece(color) {}

void Pawn::move(int eventY, int eventX, int& y, int& x, int boardHeight) {
    if (eventY >= 1 && eventY <= boardHeight && eventX == x) {
        y = eventY;
        x = eventX;
    }
}
void Pawn::capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win) {
    if ((eventY == y - 1 || eventY == y + 1) && eventX == capturedPieceX && eventY == capturedPieceY) {
        y = eventY;
        x = eventX;
        capturedPieceX = capturedPieceY = -1;
        wclear(message_win);
        wprintw(message_win, "Piece captured!");
        wrefresh(message_win);
        sleep(2);
    }
}
 const wchar_t* Pawn::getUnicodeSymbol() { return color == WHITE ? L" ♙ " : L" ♟ "; }
 const wchar_t* Pawn::getASCIISymbol() { return color == WHITE ? L" P " : L" p "; }