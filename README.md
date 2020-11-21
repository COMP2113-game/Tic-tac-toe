# Tic-tac-toe

## Team Member

Group 28

Chen Yulin (3035447398)

Wang Manlin (3035535016)

### 1. Game Description

In this project, a Tic-Tac-Toe game will be designed in which player and robot take turns to place a chess(O or X) to complete a row, a column, or a diagonal with either three O's or three X's drawn in the spaces of a grid of nine squares. The first one who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row is the winner. 

<p align="center">
  <img width="400" src="image/1.png">
</p>

### 2. Features to Be Implemented

#### Generation of Game Sets or Events

This game will allow users to choose between two different game level: Easy and Impossible. In the Easy level, the user will play against the robot which moves randomly. In the Impossible level, the user will play against an AI agent who uses minimax strategy.

#### Data Structures for Storing Game Status

A dynamic array of user-defined length and a boolean variable (indicating who is the next one to move) will be used to store the game status.

#### File Input/Output

The game can be paused and the game progress will be kept in the archive as a text (board.txt) file. When a new game is launched, the user will be asked whether to continue the game or start a new game and makes the choice by entering the command "CONT" or "NEW". If the user chooses to continue the game, the program will read the text file (board.txt) storing the game progress.

#### Dynamic Memory Management

* A dynamic char array is used to store the empty position in the function Game::randomMove() for the robot to make the random move in the easy level. The dynamic array is deleted after the robot has made a choice among the empty positions to release the memory.

* Two dynamic int arrays are used to store the player's movements and the robot's movements respectively to check if the game ends (i.e. Player's/Robot's chesspieces connect as a line). The arrays are deleted after printing out the winner result to release the memory. 

#### Program Codes in Multiple Files

* A chesspiece.h file to store the function declaration of the chesspiece

* A board.h file to store the function declaration of the board

* A game.h file to store the function declaration of the board

* A chesspiece.cpp file to define functions to set and get the label of chesspiece 

* A board.cpp file to define a series of functions to check the status of the board and specified position in it and insert chesspiece to the board

* A game.cpp file to define a series of functions of the game strategy, checking the status of game, storing and accessing the last saved game, and printing the game manual

* A tictactoe.cpp file to execute the game

* A Makefile to compile and run the game on the shell

### 3. Compilation And Execution Instructions

* Makefile is created for easy compilation. Type `make` to compile.

* Type `./game` to enjoy the funny game! 

* Choose whether to start a brand new game or continue the last saved game. Enter "CONT" or "NEW" to choose!

* You will start first and your chesspieces will be denoted by "X" while the computer's placement are denoted by "O".

* 1-9 denotes the nine position of the board. Enter any number from 1 to 9 to place your chesspiece.

* Have fun with the game please~
