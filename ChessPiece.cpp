// ChessPiece.cpp
// Chess modeller project
// 13.12.21
// Piece class definitions


// All Piece classes function definitions //


#include "ChessBoard.h"
using namespace std;


// PIECE CLASSES //

// moving one square in any direction
bool King::isValidDestinationSquare(string source_square, string destination_square, bool pieceAtDestination) const {
    int source_file = stringFileIndex(source_square);
    int source_rank = stringRankIndex(source_square);
    int destination_file = stringFileIndex(destination_square);
    int destination_rank = stringRankIndex(destination_square);
    if (destination_file >= source_file-1 && destination_file <= source_file+1 && destination_rank >= source_rank-1 && destination_rank <= source_rank+1) return true;
    else return false;
}
// never passes through any so return blank
vector<string> King::squaresPassedThrough(string source_square, string destination_square) const {
    vector<string> squares_vector;
    return squares_vector;
}
// moving along file or rank
bool Rook::isValidDestinationSquare(string source_square, string destination_square, bool pieceAtDestination) const {
    int source_file = stringFileIndex(source_square);
    int source_rank = stringRankIndex(source_square);
    int destination_file = stringFileIndex(destination_square);
    int destination_rank = stringRankIndex(destination_square);
    if (destination_file == source_file || destination_rank == source_rank) return true;
    else return false;
}
vector<string> Rook::squaresPassedThrough(string source_square, string destination_square) const {
    vector<string> squares_vector;
    int source_file = stringFileIndex(source_square);
    int source_rank = stringRankIndex(source_square);
    int destination_file = stringFileIndex(destination_square);
    int destination_rank = stringRankIndex(destination_square);
    // movement along rank
    if (destination_file == source_file) {
        // bottom to top
        if (source_rank < destination_rank) {
            for (int j = 1; source_rank+j < destination_rank; j++) {
                squares_vector.push_back(indexesToString(source_file, source_rank+j));
            }
        }
        // top to bottom
        if (source_rank > destination_rank) {
            for (int j = 1; source_rank-j > destination_rank; j++) {
                squares_vector.push_back(indexesToString(source_file, source_rank-j));
            }
        }
    }
    // movement across file
    else if (destination_rank == source_rank) {
        // left to right
        if (source_file < destination_file) {
            for (int i = 1; source_file+i < destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file+i, source_rank));
            }
        }
        // right to left
        if (source_file > destination_file) {
            for (int i = 1; source_file-i > destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file-i, source_rank));
            }
        }
    }
    return squares_vector;
}
// moving along either diagonals from the square
bool Bishop::isValidDestinationSquare(string source_square, string destination_square, bool pieceAtDestination) const {
    int source_file = stringFileIndex(source_square);
    int source_rank = stringRankIndex(source_square);
    int destination_file = stringFileIndex(destination_square);
    int destination_rank = stringRankIndex(destination_square);
    if (destination_file - destination_rank == source_file - source_rank || destination_file + destination_rank == source_file + source_rank) return true;
    else return false;
}
vector<string> Bishop::squaresPassedThrough(string source_square, string destination_square) const {
    vector<string> squares_vector;
    int source_file = stringFileIndex(source_square);
    int source_rank = stringRankIndex(source_square);
    int destination_file = stringFileIndex(destination_square);
    int destination_rank = stringRankIndex(destination_square);
    // bottom left to top right movement
    if (destination_file - destination_rank == source_file - source_rank) {
        // left to right movement
        if (source_file < destination_file) {
            for (int i = 1; source_file+i < destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file+i, source_rank+i));
            }
        }
        // right to left movement
        if (source_file > destination_file) {
            for (int i = 1; source_file-i > destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file-i, source_rank-i));
            }
        }
    }
    // top left to bottom right movement
    if (destination_file + destination_rank == source_file + source_rank) {
        // left to right movement
        if (source_file < destination_file) {
            for (int i = 1; source_file+i < destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file+i, source_rank-i));
            }
        }
        // right to left movement
        if (source_file > destination_file) {
            for (int i = 1; source_file-i > destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file-i, source_rank+i));
            }
        }
    }
    return squares_vector;
}
// rook-like or bishop-like movement both allowed
bool Queen::isValidDestinationSquare(string source_square, string destination_square, bool pieceAtDestination) const {
    int source_file = stringFileIndex(source_square);
    int source_rank = stringRankIndex(source_square);
    int destination_file = stringFileIndex(destination_square);
    int destination_rank = stringRankIndex(destination_square);
    if (destination_file == source_file || destination_rank == source_rank || destination_file - destination_rank == source_file - source_rank || destination_file + destination_rank == source_file + source_rank) return true;
    else return false;
}
vector<string> Queen::squaresPassedThrough(string source_square, string destination_square) const {
    vector<string> squares_vector;
    int source_file = stringFileIndex(source_square);
    int source_rank = stringRankIndex(source_square);
    int destination_file = stringFileIndex(destination_square);
    int destination_rank = stringRankIndex(destination_square);
    // Rook-like movement
    // movement along rank
    if (destination_file == source_file) {
        // bottom to top
        if (source_rank < destination_rank) {
            for (int j = 1; source_rank+j < destination_rank; j++) {
                squares_vector.push_back(indexesToString(source_file, source_rank+j));
            }
        }
        // top to bottom
        if (source_rank > destination_rank) {
            for (int j = 1; source_rank-j > destination_rank; j++) {
                squares_vector.push_back(indexesToString(source_file, source_rank-j));
            }
        }
    }
    // movement across file
    else if (destination_rank == source_rank) {
        // left to right
        if (source_file < destination_file) {
            for (int i = 1; source_file+i < destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file+i, source_rank));
            }
        }
        // right to left
        if (source_file > destination_file) {
            for (int i = 1; source_file-i > destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file-i, source_rank));
            }
        }
    }
    // Bishop-like movement
    // bottom left to top right movement
    if (destination_file - destination_rank == source_file - source_rank) {
        // left to right movement
        if (source_file < destination_file) {
            for (int i = 1; source_file+i < destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file+i, source_rank+i));
            }
        }
        // right to left movement
        if (source_file > destination_file) {
            for (int i = 1; source_file-i > destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file-i, source_rank-i));
            }
        }
    }
    // top left to bottom right movement
    if (destination_file + destination_rank == source_file + source_rank) {
        // left to right movement
        if (source_file < destination_file) {
            for (int i = 1; source_file+i < destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file+i, source_rank-i));
            }
        }
        // right to left movement
        if (source_file > destination_file) {
            for (int i = 1; source_file-i > destination_file; i++) {
                squares_vector.push_back(indexesToString(source_file-i, source_rank+i));
            }
        }
    }
    return squares_vector;
}
// +/-1 rank and +/-2 file, or vice versa
bool Knight::isValidDestinationSquare(string source_square, string destination_square, bool pieceAtDestination) const {
    int source_file = stringFileIndex(source_square);
    int source_rank = stringRankIndex(source_square);
    int destination_file = stringFileIndex(destination_square);
    int destination_rank = stringRankIndex(destination_square);
    if (((destination_file == source_file-1 || destination_file == source_file+1) && (destination_rank == source_rank-2 || destination_rank == source_rank+2)) || ((destination_file == source_file-2 || destination_file == source_file+2) && (destination_rank == source_rank-1 || destination_rank == source_rank+1))) return true;
    else return false;
}
// never called - but should return blank regardless
vector<string> Knight::squaresPassedThrough(string source_square, string destination_square) const {
    vector<string> squares_vector;
    return squares_vector;
}
// rules are rather complex
// no-taking veritically implemented in ChessBoard::submitMove
bool Pawn::isValidDestinationSquare(string source_square, string destination_square, bool pieceAtDestination) const {
    int source_file = stringFileIndex(source_square);
    int source_rank = stringRankIndex(source_square);
    int destination_file = stringFileIndex(destination_square);
    int destination_rank = stringRankIndex(destination_square);
    // move up rank for white, down for black
    if (colour == "White") {
        // initial double move
        if (intToRank(source_rank) == '2') {
            if (destination_file == source_file && intToRank(destination_rank) == '4') return true;
        }
        // taking diagonally
        if (pieceAtDestination) {
            if ((destination_file == source_file+1 || destination_file == source_file-1) && destination_rank == source_rank+1) return true;
        }
        // normal verical movement
        if (destination_file == source_file && destination_rank == source_rank+1) return true;
        else return false;
    }
    if (colour == "Black") {
        if (intToRank(source_rank) == '7') {
            if (destination_file == source_file && intToRank(destination_rank) == '5') return true;
        }
        if (pieceAtDestination) {
            if ((destination_file == source_file+1 || destination_file == source_file-1) && destination_rank == source_rank-1) return true;
        }
        if (destination_file == source_file && destination_rank == source_rank-1) return true;
        else return false;
    }
    else return false;
}
// can move through a square only if doing initial double move
vector<string> Pawn::squaresPassedThrough(string source_square, string destination_square) const {
    vector<string> squares_vector;
    int source_file = stringFileIndex(source_square);
    int source_rank = stringRankIndex(source_square);
    int destination_rank = stringRankIndex(destination_square);
    if (colour == "White") {
        if (destination_rank == source_rank+2) {
            squares_vector.push_back(indexesToString(source_file, source_rank+1));
        }
    }
    if (colour == "Black") {
        if (destination_rank == source_rank-2) {
            squares_vector.push_back(indexesToString(source_file, source_rank-1));
        }
    }
    return squares_vector;
}