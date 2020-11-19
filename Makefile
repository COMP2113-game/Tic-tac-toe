game: tictactoe.cpp Board.cpp Game.cpp Chesspiece.cpp 
	g++ tictactoe.cpp Board.cpp Game.cpp Chesspiece.cpp -o game
clean:
    rm -f game board.txt

deleteSavedGame:
    rm board.txt

.PHONY: clean deleteSavedGame
