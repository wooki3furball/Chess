/*
Author: Michael Bopp
Filename: main.cpp
Description: File that has driver logic for the chess program.
Date Created: 07/05/23
Last Modified: 08/01/23
*/

#include "main.h"

// Initialize the terminal settings
void initTerminal() {
    setlocale(LC_ALL, ""); // For Unicode
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    noecho();
    curs_set(0);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    ChessBoard::notation_mode = true;
}

// Calculate the offsets for the chess board
std::pair<int, int> calculateOffsets() {
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    int offsetX = (maxX - 8 * 4) / 2;
    int offsetY = (maxY - 8) / 2;
    offsetX += 4;
    offsetY -= 2;
    return {offsetX, offsetY};
}

// Set up the pieces on the chess board
void setupPieces(ChessBoard& chessBoard) {
    // Define pieces here...
  
	King whiteKing(WHITE);
    Queen whiteQueen(WHITE);
    Rook whiteRook(WHITE);
    Bishop whiteBishop(WHITE);
    Knight whiteKnight(WHITE);
    Pawn whitePawn(WHITE);

    King blackKing(BLACK);
    Queen blackQueen(BLACK);
    Rook blackRook(BLACK);
    Bishop blackBishop(BLACK);
    Knight blackKnight(BLACK);
    Pawn blackPawn(BLACK);

    // Set up black pieces
    for(int i = 0; i < 8; i++){
        if(i==0 || i==7) {
            chessBoard.placePiece(new Rook(BLACK), i, 0);
        } else if(i==1 || i==6) {
            chessBoard.placePiece(new Knight(BLACK), i, 0);
        } else if(i==2 || i==5) {
            chessBoard.placePiece(new Bishop(BLACK), i, 0);
        } else if(i==3) {
            chessBoard.placePiece(new Queen(BLACK), i, 0);
        } else {
            chessBoard.placePiece(new King(BLACK), i, 0);
        }
        chessBoard.placePiece(new Pawn(BLACK), i, 1);
    }

    // Set up white pieces
    for(int i = 0; i < 8; i++){
        if(i==0 || i==7) {
            chessBoard.placePiece(new Rook(WHITE), i, 7);
        } else if(i==1 || i==6) {
            chessBoard.placePiece(new Knight(WHITE), i, 7);
        } else if(i==2 || i==5) {
            chessBoard.placePiece(new Bishop(WHITE), i, 7);
        } else if(i==3) {
            chessBoard.placePiece(new Queen(WHITE), i, 7);
        } else {
            chessBoard.placePiece(new King(WHITE), i, 7);
        }
        chessBoard.placePiece(new Pawn(WHITE), i, 6);
    }
}

// Handle the mouse click events
void handleMouseClick(ChessBoard& chessBoard, MEVENT& event, int offsetX, int offsetY, int& selected_x, int& selected_y) {

    // Calculate board coordinates
    int x = (event.x - offsetX) / 2;
    int y = (event.y - offsetY);

    // If a piece was already selected
    if (selected_x != -1 && selected_y != -1) {
        // Try to move the selected piece
        ChessPiece* piece = chessBoard.getPieceAt(selected_x, selected_y);
        if (piece != nullptr) {
            chessBoard.movePiece(selected_x, selected_y, x, y);
        }

        // Deselect the piece
        selected_x = -1;
        selected_y = -1;
    } else {
        // Select the piece
        ChessPiece* piece = chessBoard.getPieceAt(x, y);
        if (piece != nullptr) {
            selected_x = x;
            selected_y = y;
        }
    }
}

// The main game loop
bool gameLoop(ChessBoard& chessBoard, MEVENT& event, int offsetX, int offsetY) {
    static int selected_x = -1;
    static int selected_y = -1;

    while (true) {
        drawClock(0, 40);
        drawExit(0, 0); // Top Left
        refresh();
        int ch = getch();

        switch (ch) {
            case 'x':
            case 'X':
                ChessPiece::ascii_mode = !ChessPiece::ascii_mode;
                chessBoard.drawBoard();
                break;
            case 'z':
            case 'Z':
                return false;
            case 'c':
            case 'C':
                ChessBoard::notation_mode = !ChessBoard::notation_mode;
                chessBoard.drawBoard();
                break;
            case KEY_MOUSE:
                if (getmouse(&event) == OK) { // Get mouse event
                    if (event.bstate & BUTTON1_CLICKED) { // Left button clicked
                        mvprintw(1, 0, "Clicked at: %d, %d", event.x, event.y); // Print coordinates of the mouse click
                        refresh();
                        if (event.y == 0 && event.x >= offsetX && event.x < offsetX + 6) { // Exit button clicked
                            return false; // Return false when exit button is clicked
                        } else {
                            handleMouseClick(chessBoard, event, offsetX, offsetY, selected_x, selected_y);
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
    return true;
}

int main() {
    initTerminal();

    MEVENT event;

    auto [offsetX, offsetY] = calculateOffsets();

    ChessBoard chessBoard(offsetX, offsetY);
    chessBoard.drawBoard();

    setupPieces(chessBoard);

    bool continueGame = gameLoop(chessBoard, event, offsetX, offsetY);

    if (!continueGame){
        endwin();
        return 0;
    }
    refresh();
    getch();
    return 0;
}