CC=g++ -Wall

chess: ChessBoard.o ChessMain.o ChessPiece.o ChessHelpers.o
	$(CC) -g ChessMain.o ChessBoard.o ChessPiece.o ChessHelpers.o -o chess
ChessMain.o: ChessMain.cpp ChessBoard.h
	$(CC) -g -c ChessMain.cpp
ChessBoard.o: ChessBoard.cpp ChessBoard.h
	$(CC) -g -c ChessBoard.cpp
ChessPiece.o: ChessPiece.cpp ChessBoard.h
	$(CC) -g -c ChessPiece.cpp
ChessHelpers.o: ChessHelpers.cpp ChessBoard.h
	$(CC) -g -c ChessHelpers.cpp

.PHONY : clean
clean:
	rm -f *.o chess