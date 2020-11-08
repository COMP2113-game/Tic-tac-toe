#TIC TAC TOE

A simple TicTacToe program with nice console output written entirely in C++. 

##Introduction
A Tic Tac Toe program lets the user choose his/her piece on a 3X3 board. Your goal is to align 3 of the same piece in a row/column/diagonal to win the game.

The computer (BAD GUY) will try to either win its own by doing the same, or it will block your winning ways. 

Try to beat it!

##Cool Points
If you tried to play this game, you will notice some very interesting colors on the console, as well as the game's almost god-like AI.

How did I do it, you ask?

* Console colors for the beautiful gameplay 
* Minimax algorithm, [Read Wikipedia entry here](http://en.wikipedia.org/wiki/Minimax#Minimax_algorithm_with_alternate_moves) for the God-like AI

##Classes
There are three distinct classes in this TicTacToe game:
* `Game` - This is the main game logic with minimax algorithm implemented
* `Board` - This is the board for the game, has 3X3 dimensions
* `chesspiece` - This is the piece that will be used for the game. Could have read "TicTac" and "Toe" but I decided that chesspiece is a little more generic.

Finally, there is one important class that runs the game: `tictactoegame`.

##How to run
This is written in C++, so to compile it, you need g++. The instructions below are for Mac/Linux:

* log into Terminal
* `cd` to the folder containing this game
* type: `make` for easy compilation (I already included all the necessary files to make it easy for you to compile)
[Alternatively: you can type `g++ tictactoeGame.cpp Board.cpp Game.cpp chesspiece.cpp -o game` to compile the game]
* type: `./game` to compile the game and you're done!


For Windows users, I think you might need Cygwin to achieve something similar. I haven't done a lot of programming in Windows, so that's a foreign land for me. For anyone intending to run this in Windows, please let me know and I can find out more about that.

[Last updated: July 13, 2013] 
