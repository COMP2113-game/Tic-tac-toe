Chesspiece.o: Chesspiece.cpp Chesspiece.h
    g++ -pedantic-errors -std=c++11 -c Chesspiece.cpp

Board.o: Board.cpp Board.h Chesspiece.h
    g++ -pedantic-errors -std=c++11 -c Board.cpp

Game.o: Game.cpp Game.h Board.h Chesspiece.h
    g++ -pedantic-errors -std=c++11 -c Game.cpp

tictactoe.o: tictactoe.cpp Game.h Board.h Chesspiece.h
    g++ -pedantic-errors -std=c++11 -c tictactoe.cpp

game: tictactoe.o Game.o Board.o Chesspiece.o
    g++ -pedantic-errors -std=c++11 tictactoe.o Game.o Board.o Chesspiece.o -o game

