// ChessBoard.cpp
// Chess modeller project
// 13.12.21
// ChessBoard class definitions

// note:in general store squares in the array like:
// "A1" == [0][0], "A2" == [0][1], ..., "B8" == [1][7], etc.


#include "ChessBoard.h"
using namespace std;


// CHESSBOARD CLASS FUNCTIONS //

ChessBoard::ChessBoard() {
    startingBoard();
    cout << "A new chess game is started!\n";
}

ChessBoard::~ChessBoard() {
    wipeBoard();
}

void ChessBoard::resetBoard() {
    turn = "White";
    wipeBoard();
    startingBoard();
    cout << "A new chess game is started!\n";
}

// delete any pieces left on the board
void ChessBoard::wipeBoard() {
    for (int i = 0; i < SIZE_OF_BOARD; i++) {
        for (int j = 0; j < SIZE_OF_BOARD; j++) {
            if (board[i][j] != nullptr) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
}

// create and assign starting pieces and set the rest of the board to nullptr
void ChessBoard::startingBoard() {
    for (int i = 0; i < SIZE_OF_BOARD; i++) {
        for (int j = 2; j < SIZE_OF_BOARD - 2; j++) {
            board[i][j] = nullptr;
        }
    }
    for (int i = 0; i < SIZE_OF_BOARD; i++) {
        board[i][1] = new Pawn("White");
        board[i][SIZE_OF_BOARD-2] = new Pawn("Black");
    }
    for (int i = 0; i < SIZE_OF_BOARD; i++) {
        if (i == 0 || i == SIZE_OF_BOARD-1) {
            board[i][0] = new Rook("White");
            board[i][SIZE_OF_BOARD-1] = new Rook("Black");
        }
        if (i == 1 || i == SIZE_OF_BOARD-2) {
            board[i][0] = new Knight("White");
            board[i][SIZE_OF_BOARD-1] = new Knight("Black");
        }
        if (i == 2 || i == SIZE_OF_BOARD-3) {
            board[i][0] = new Bishop("White");
            board[i][SIZE_OF_BOARD-1] = new Bishop("Black");
        }
        if (i == 3) {
            board[i][0] = new Queen("White");
            board[i][SIZE_OF_BOARD-1] = new Queen("Black");
        }
        if (i == SIZE_OF_BOARD-4) {
            board[i][0] = new King("White");
            board[i][SIZE_OF_BOARD-1] = new King("Black");
        }
    }
}

// main interface function
void ChessBoard::submitMove(string source_square, string destination_square) {
    
    // basic sanity checks

    try { // catch this exception here or not and then don't worry about it
        if (!isOnBoard(source_square, destination_square)) { cout << "That is not a square on the board!" << endl; return; }
    } catch(string square) { cout << "Invalid square string!" << endl; return; }

    if (!hasPieceAtSquare(source_square)) { cout << "There is no piece at position " << source_square << "!" << endl; return; }

    if (pieceAtSquare(source_square).getColour() != turn) { cout << "It is not " << pieceAtSquare(source_square).getColour() << "'s turn to move!" << endl; return; }

    if (!validMove(source_square, destination_square)) { cout << pieceAtSquare(source_square) << " cannot move to " << destination_square << "!" << endl; return; }

    // remember state of board in case of undoing the move later
    BoardArray previous_board = board;
    // taken_piece info for printing later
    bool take_piece = false;
    string taken_piece_colour;
    string taken_piece_type;
    if (pointerAtSquare(destination_square) != nullptr) {
        taken_piece_colour = pointerAtSquare(destination_square)->getColour();
        taken_piece_type = pointerAtSquare(destination_square)->getPieceType();
        take_piece = true;
    }

    // make the move
    makeMove(source_square, destination_square);

    // undo if turn player put themselves 'in check'
    if (turnPlayerInCheck()) {
        cout << pieceAtSquare(source_square) << " cannot move to " << destination_square << "!" << endl;
        board = previous_board;
        return;
    }
    
    ///////// MOVE MADE ///////////

    // otherwise announce that the move is okay
    cout << pieceAtSquare(destination_square) << " moves from " << source_square << " to " << destination_square;
    if (take_piece) {
        cout << " taking " << taken_piece_colour << "'s " << taken_piece_type;
    }
    cout << endl;

    changeTurn();

    if (turnPlayerInCheck()) {
        if (checkMate()) { endGame("checkmate"); return; }
    }
    else {
        if (staleMate()) { endGame("stalemate"); return; }
    }
    // if the game is not over, ouptut that they are simply 'in check'
    if (turnPlayerInCheck()) { cout << turn << " is in check" << endl; }
}

bool ChessBoard::hasPieceAtSquare(string square) const {
    if (pointerAtSquare(square) == nullptr) {
        return false;
    }
    else return true;
}

Piece& ChessBoard::pieceAtSquare(string square) const {
    return *pointerAtSquare(square);
}

// note: not for reassigning pointers to new pieces
Piece* ChessBoard::pointerAtSquare(string square) const {
    return board[stringFileIndex(square)][stringRankIndex(square)];
}

bool ChessBoard::squaresAreEmpty(vector<string> squares) const {
    for (int i = 0; i < int(squares.size()); i++) {
        if (pointerAtSquare(squares[i]) != nullptr) { return false; }
    }
    return true;
}

bool ChessBoard::validMove(string source_square, string destination_square) const {
    // bool needed for Pawn case
    bool piece_at_destination = false;
    if (hasPieceAtSquare(destination_square)) {
        if (pieceAtSquare(destination_square).getColour() == pieceAtSquare(source_square).getColour()) return false;
        else piece_at_destination = true;
    }
    // check Pawn is not trying to take a piece while moving vertically
    // do this here because Piece doesn't know about ChessBoard
    if (pieceAtSquare(source_square).getPieceType() == "Pawn" && stringFileIndex(source_square) == stringFileIndex(destination_square))  { 
        if (hasPieceAtSquare(destination_square)) return false;
    }
    // now check normal move rules for the piece
    if (!pieceAtSquare(source_square).isValidDestinationSquare(source_square, destination_square, piece_at_destination)) return false;
    // check pieces are not in the way
    // works because Knight & King return blank from squaresPassedThrough
    if (!squaresAreEmpty(pieceAtSquare(source_square).squaresPassedThrough(source_square, destination_square))) return false;

    return true;
}

// note: deletes taken piece
void ChessBoard::makeMove(string source_square, string destination_square) {
    if (pointerAtSquare(destination_square) != nullptr) {
        delete pointerAtSquare(destination_square);
    }
    board[stringFileIndex(destination_square)][stringRankIndex(destination_square)] = board[stringFileIndex(source_square)][stringRankIndex(source_square)];
    board[stringFileIndex(source_square)][stringRankIndex(source_square)] = nullptr;
}

void ChessBoard::changeTurn() {
    if (turn == "White") turn = "Black";
    else if (turn == "Black") turn = "White";
    else cout << "It is no-one's turn! The game is over!" << endl;
}

bool ChessBoard::turnPlayerInCheck() { 
    string king_square;
    for (int i = 0; i < SIZE_OF_BOARD; i++) {
        for (int j = 0; j < SIZE_OF_BOARD; j++) {
            if (board[i][j] != nullptr) {
                if (board[i][j]->getColour() == turn && board[i][j]->getPieceType() == "King") {
                    king_square = indexesToString(i,j);
                }
            }
        }
    }
    string source_square;
    for (int i = 0; i < SIZE_OF_BOARD; i++) {
        for (int j = 0; j < SIZE_OF_BOARD; j++) {
            if (board[i][j] != nullptr && board[i][j]->getColour() != turn) {
                source_square = indexesToString(i,j);
                if (validMove(source_square, king_square)) return true;
            }
        }
    }
    return false; 
}

bool ChessBoard::checkMate() { 
    string source_square;
    string destination_square;
    // just brute force it :)
    for (int i = 0; i < SIZE_OF_BOARD; i++) {
        for (int j = 0; j < SIZE_OF_BOARD; j++) {
            if (board[i][j] != nullptr && board[i][j]->getColour() == turn) {
                source_square = indexesToString(i,j);
                for (int x = 0; x < SIZE_OF_BOARD; x++) {
                    for (int y = 0; y < SIZE_OF_BOARD; y++) {
                        destination_square = indexesToString(x,y);
                        if (validMove(source_square, destination_square)) {
                            // move the piece out of the way if it would be taken because makeMove would delete it otherwise
                            Piece *temp = nullptr;
                            if (pointerAtSquare(destination_square) != nullptr) {
                                temp = pointerAtSquare(destination_square);
                                board[stringFileIndex(destination_square)][stringRankIndex(destination_square)] = nullptr;
                            }
                            makeMove(source_square, destination_square);
                            if (!turnPlayerInCheck()) {
                                makeMove(destination_square, source_square);
                                board[stringFileIndex(destination_square)][stringRankIndex(destination_square)] = temp;
                                return false;
                            }
                            else {
                                makeMove(destination_square, source_square);
                                board[stringFileIndex(destination_square)][stringRankIndex(destination_square)] = temp;
                                // don't return until we have checked every possible move and found no results
                            } 
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool ChessBoard::staleMate() {
    // this is actually the same condition as checkMate, just starting from a not-in-check state :)
    // i.e. we still just want any move that is valid and leaves us not-in-check
    return checkMate();
}

void ChessBoard::endGame(string endstate) {
    cout << turn << " is in " << endstate << endl;
    // ensure that no more moves can be made be setting a 'null-ish' turn value
    turn = "NA"; 
}

// does the job...
void ChessBoard::printBoard() {
    for (int j = 0; j < SIZE_OF_BOARD; j++) {
        cout << intToRank(j) << " : " << endl;
        for (int i = 0; i < SIZE_OF_BOARD; i++) {
            if (board[i][j] != nullptr) {
                cout << intToFile(i) << intToRank(j) << ": " << *board[i][j] << endl;
            }
        }
        cout << endl;
    }
}