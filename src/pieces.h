/*
Author: Michael Bopp
Filename: pieces.h
Description:
Date Created: 07/05/23
Last Modified: 07/31/23
*/

#ifndef PIECES_H
#define PIECES_H

#include <ncurses.h>
#include <locale.h>
#include <iostream>
#include <time.h>
#include <utility>
#include <vector>
#include <unistd.h>
#include <stdexcept>

#define RANK_SIZE 8 // Row in Chess
#define FILE_SIZE 8 // Column in Chess

enum Color {
    WHITE = 'w',
    BLACK = 'b'
};

enum PieceType {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
};

class ChessPiece {
protected:
    Color color;
    PieceType type;

public:
    static bool ascii_mode;
    const wchar_t* getSymbol();
    virtual const wchar_t* getUnicodeSymbol() = 0;
    virtual const wchar_t* getASCIISymbol() = 0;
    ChessPiece(Color color);
    virtual void move(int eventY, int eventX, int& y, int& x, int boardHeight) = 0;
    virtual void capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win) = 0;

    virtual ~ChessPiece() {}

    Color getColor() const;
    void setColor(Color newColor);

    PieceType getType() const {
        return type;
    }

    void setType(PieceType type){
        this->type = type;
    }

};

class King: public ChessPiece{
public:
    King(Color color);
    ~King() override {};
    virtual void move(int eventY, int eventX, int& y, int& x, int boardHeight);
    virtual void capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win);
    const wchar_t* getUnicodeSymbol() override;
    const wchar_t* getASCIISymbol() override;
};

class Queen: public ChessPiece{
public:
    Queen(Color color);
    ~Queen() override {};
    virtual void move(int eventY, int eventX, int& y, int& x, int boardHeight);
    virtual void capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win);
    const wchar_t* getUnicodeSymbol() override;
    const wchar_t* getASCIISymbol() override;
};

class Rook: public ChessPiece{
public:
    Rook(Color color);
    ~Rook() override {};
    virtual void move(int eventY, int eventX, int& y, int& x, int boardHeight);
    virtual void capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win);
    const wchar_t* getUnicodeSymbol() override;
    const wchar_t* getASCIISymbol() override;
};

class Bishop: public ChessPiece{
public:
    Bishop(Color color);
    ~Bishop() override {};
    virtual void move(int eventY, int eventX, int& y, int& x, int boardHeight);
    virtual void capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win);
    const wchar_t* getUnicodeSymbol() override;
    const wchar_t* getASCIISymbol() override;
};

class Knight: public ChessPiece{
public:
    Knight(Color color);
    ~Knight() override {};
    virtual void move(int eventY, int eventX, int& y, int& x, int boardHeight);
    virtual void capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win);
    const wchar_t* getUnicodeSymbol() override;
    const wchar_t* getASCIISymbol() override;
};

class Pawn: public ChessPiece{
public:
    Pawn(Color color);
    ~Pawn() override {};
    virtual void move(int eventY, int eventX, int& y, int& x, int boardHeight);
    virtual void capture(int eventY, int eventX, int& y, int& x, int& capturedPieceX, int& capturedPieceY, WINDOW* message_win);
    const wchar_t* getUnicodeSymbol() override;
    const wchar_t* getASCIISymbol() override;
};

#endif //PIECES_H