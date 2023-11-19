// ChessHelpers.cpp
// Chess modeller project
// 13.12.21
// Helper functions definitions

#include "ChessBoard.h"
using namespace std;

// ARRAY INDEX/FILE AND RANK HELPER FUNCTIONS //

char intToFile(int index) {
    return index + 'A';
}
char intToRank(int index) {
    return index + '1';
}
int fileToInt(char file) {
    return file - 'A';
}
int rankToInt(char rank) {
    return rank - '1';
}
int stringFileIndex(string square) {
    return square.at(0) - 'A';
}
int stringRankIndex(string square) {
    return square.at(1) - '1';
}
string indexesToString(int file, int rank) {
    string square;
    square.push_back(intToFile(file));
    square.push_back(intToRank(rank));
    return square;
}

// STRING VALIDITY CHECKERS //

// throws string as exception if wrong length
// should only be called by submitMove once (twice) per move
bool isOnBoard(string square) {
    if (square.length() != 2) throw square;
    if (square.at(0) < 'A' || square.at(0) > 'H'
        || square.at(1) < '1' || square.at(1) > '8') return false;
    else return true; 
}
bool isOnBoard(string source_square, string destination_square) {
    if (isOnBoard(source_square) && isOnBoard(destination_square)) return true;
    else return false;
}