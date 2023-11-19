// ChessBoard.h
// Chess modeller project
// 13.12.21
// header file

// Interface with a ChessBoard object using submitMove("D2","D4") calls in main
// Program all moves in main
// Output of game to command line

// Model will check all basic moves of the game to validate moves
// and tells the user when a player is 'in check', 'checkmate' or 'stalemate'

/* SOURCES
    std template library:
        https://www.geeksforgeeks.org/the-c-standard-template-library-stl/
    enums:
        https://www.programiz.com/cpp-programming/enumeration
    overloading operator[] for 2D arrays:
        https://stackoverflow.com/questions/6969881/operator-overload
    ascii table:
        https://www.rapidtables.com/code/text/ascii-table.html
    std::array:
        https://en.cppreference.com/w/cpp/container/array/at
    std::string:
        https://www.cplusplus.com/reference/string/string/
*/

#pragma once


#include <string>
#include <array>
#include <vector>
#include <iostream>


int const SIZE_OF_BOARD = 8;

class Piece;
typedef std::array<std::array<Piece*, SIZE_OF_BOARD>, SIZE_OF_BOARD> BoardArray;

// Helper functions //
char intToFile(int index);
char intToRank(int index);
int fileToInt(char file);
int rankToInt(char rank);
int stringFileIndex(std::string square);
int stringRankIndex(std::string square);
std::string indexesToString(int file, int rank);
bool isOnBoard(std::string square);
bool isOnBoard(std::string source_square, std::string destination_square);

// Piece class heirarchy //

// isValidDestinationSquare contains piece specific moving rules
// getPieceType is also overridden

class Piece {
protected:
    std::string colour;
public:
    Piece() { colour = "White"; }
    Piece(std::string colour) : colour(colour) {};
    virtual ~Piece() {}; // silences one warning
    std::string getColour() const { return colour; }
    virtual std::string getPieceType() const { return "none"; }
    virtual bool isValidDestinationSquare(std::string source_square, std::string destination_square, bool pieceAtDestination) const { return false; }
    virtual std::vector<std::string> squaresPassedThrough(std::string source_square, std::string destination_square) const { return std::vector<std::string>(); }
    friend std::ostream& operator<<(std::ostream& o, const Piece& p) { o << p.getColour() << "'s " << p.getPieceType(); return o; }
};
class King : public Piece {
public:
    King() : Piece() {};
    King(std::string colour) : Piece(colour) {} 
    std::string getPieceType() const override { return "King"; }
    bool isValidDestinationSquare(std::string source_square, std::string destination_square, bool pieceAtDestination) const override;
    std::vector<std::string> squaresPassedThrough(std::string source_square, std::string destination_square) const override;
};
class Rook : public Piece {
public:
    Rook() : Piece() {};
    Rook(std::string colour) : Piece(colour) {} 
    std::string getPieceType() const override { return "Rook"; }
    bool isValidDestinationSquare(std::string source_square, std::string destination_square, bool pieceAtDestination) const override;
    std::vector<std::string> squaresPassedThrough(std::string source_square, std::string destination_square) const  override;
};
class Bishop : public Piece {
public:
    Bishop() : Piece() {};
    Bishop(std::string colour) : Piece(colour) {} 
    Bishop(Bishop &b);
    std::string getPieceType() const override { return "Bishop"; }
    bool isValidDestinationSquare(std::string source_square, std::string destination_square, bool pieceAtDestination) const override;
    std::vector<std::string> squaresPassedThrough(std::string source_square, std::string destination_square) const override;
};
class Queen : public Piece {
public:
    Queen() : Piece() {};
    Queen(std::string colour) : Piece(colour) {} 
    std::string getPieceType() const override { return "Queen"; }
    bool isValidDestinationSquare(std::string source_square, std::string destination_square, bool pieceAtDestination) const override;
    std::vector<std::string> squaresPassedThrough(std::string source_square, std::string destination_square) const override;
};
class Knight : public Piece {
public:
    Knight() : Piece() {};
    Knight(std::string colour) : Piece(colour) {};
    std::string getPieceType() const override { return "Knight"; }
    bool isValidDestinationSquare(std::string source_square, std::string destination_square, bool pieceAtDestination) const override;
    std::vector<std::string> squaresPassedThrough(std::string source_square, std::string destination_square) const override;
};
class Pawn : public Piece {
public:
    Pawn() : Piece() {}; 
    Pawn(std::string colour) : Piece(colour) {}
    std::string getPieceType() const override { return "Pawn"; }
    bool isValidDestinationSquare(std::string source_square, std::string destination_square, bool pieceAtDestination) const override;
    std::vector<std::string> squaresPassedThrough(std::string source_square, std::string destination_square) const override;
};

// ChessBoard models a game in its entireity
// Create a starting board with default constructor
// Call submitMove("D4","D5") etc. to simulate the game
// Reset the board with resetBoard()
class ChessBoard {
    std::string turn = "White";
    // 2D array of Piece base class pointers
    BoardArray board;
public:
    
    // sets up the initial gamestate
    ChessBoard();
    ~ChessBoard();

    // interface functions //

    void submitMove(std::string source_square, std::string destination_square);
    void resetBoard();

    // helper functions //

    void wipeBoard();
    void startingBoard();
    // checks if there is a piece at given square
    bool hasPieceAtSquare(std::string square) const;
    Piece& pieceAtSquare(std::string square) const;
    Piece* pointerAtSquare(std::string square) const;
    bool squaresAreEmpty(std::vector<std::string> squares) const;
    // calls isValidDestinationSquare on the Piece at source_square
    bool validMove(std::string source_square, std::string destination_square) const;
    // moves a piece and takes an opponent piece
    // YOU must hold and reassign the destination_square pointer
    // if you don't want the piece to be taken
    void makeMove(std::string source_square, std::string destination_square);
    void changeTurn();
    // note: the following checks are not marked const because they call makeMove but they do undo the move themselves so return the board to its state at call
    // true if player who just moved is now 'in check'
    bool turnPlayerInCheck();
    // true if player is checkmate
    bool checkMate();
    // true if player is stalemate
    bool staleMate();
    // ends the game as checkmate or stalemate for next player and prints message
    void endGame(std::string endstate);

    // debug functions //

    void printBoard();
};