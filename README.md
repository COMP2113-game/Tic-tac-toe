# advance-tic-tac-toe

# 1. Team Member

Group 28

Chen Yulin (3035447398)

Wang ManLin (3035535016)

## Tic-tac-toe

### 1. Game Description

In this project, a Tic-Tac-Toe game will be designed in which two players take turns to place a chess(O or X) to complete a row, a column, or a diagonal with either three O's or three X's drawn in the spaces of a grid of nine squares. The first one who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row is the winner. 

<p align="center">
  <img width="400" src="image/1.png">
</p>

### 2. Features to be implemented

#### Generation of game sets or events

This game will allow users to choose between two different game level: Easy and Impossible. In the Easy level, the user will play against the computer which moves randomly. In the Impossible level, the user will play against an AI agent who uses minimax strategy.

#### Data structures for storing game status: 

A 3 * 3 array and a boolean variable (indicating who is the next one to move) will be used to store the game status.

#### File input/output

The game can be paused and the game progress will be kept in the archive as a text (board.txt) file. When a new game is launched, the user will be asked whether to continue the game or start a new game and makes the choice by entering the command "CONT" or "NEW". If the user chooses to continue the game, the program will read the text file (board.txt) storing the game progress.

#### Dynamic memory management

* The board of the game is stored in dynamic char array and can be deleted at the end of game to free up the memory.

#### Program codes in multiple files

* A chesspiece.h file to store the function declaration of the chesspiece

* A board.h file to store the function declaration of the board

* A game.h file to store the function declaration of the board

* A chesspiece.cpp file to define functions to set and get the label of chesspiece 

* A board.cpp file to define a series of functions to check the status of the board and specified position in it and insert chesspiece to the board

* A game.cpp file to define a series of functions of the game strategy, checking the status of game, storing and accessing the last saved game, and printing the game manual

* A tictactoe.cpp file to execute the game

* A Makefile to compile and run the game on the shell

### 3. Tips for playing the game

* Makefile is created for easy compilation. Enter "make" to compile.

* Enter "./game" to enjoy the funny game! 

* Choose whether to start a brand new game or continue the last saved game. Enter "CONT" or "NEW" to choose!

* You will start first and your chesspieces will be denoted by "X" while the computer's placement are denoted by "O".

* 1-9 denotes the nine position of the board. Enter any number from 1 to 9 to place your chesspiece.

* Have fun with the game please~
