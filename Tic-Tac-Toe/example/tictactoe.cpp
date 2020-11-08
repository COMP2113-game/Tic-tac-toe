/*  Author: Zhia Chong
    Program: tictactoe.cpp
    Date: 6/12/2013
*/
#include <iostream>  
#include <string>

/* Board, game and chess piece class files */
#include "chesspiece.h"
#include "Board.h"
#include "Game.h"
using namespace std;

// sets the console output to different colors 
#define RED "\033[22;31m" 
#define RESET "\033[0m" //resets to console output to default color
#define GREY "\033[22;37m"
#define LIGHT_RED "\033[01;31m"
#define LIGHT_GREEN "\033[01;32m"
#define LIGHT_PURPLE "\033[01;35m"
#define LIGHT_CYAN "\033[01;36m"

#define INFINITY 1073741824
#define MAX_BOARD_SIZE 10

typedef enum {player = 1, computer = -1, allelse = 0} GameDecision;

static int positionMax, positionMin;

static char board[MAX_BOARD_SIZE];

void print_board();

void printDirections();

void startGame();

GameDecision checkForWinners(char board[]);

int minimax(bool playerTurn, char board[], int n);

bool isValidInput(int input);

bool isGameADraw(char board[]);

bool isPositionEmpty(int position);

bool checkForConnectingLines(char ch);

int main()
{
    printDirections();

    for(int i = 1; i < MAX_BOARD_SIZE; i++)
        board[i] = '_';

    cout << "The board is empty now." << endl;
    print_board();

    cout << GREY << "\n\nAs a guest, you can start first! You will be X." << RESET << endl;
    startGame();

    return 0;
}

void startGame()
{
    string in = "";
    bool noWinnersYet = true;

    for(int i = 1; i < MAX_BOARD_SIZE && noWinnersYet; i++)
    {
        cin >> in;
        int input = atoi(in.c_str());

        while  (!isPositionEmpty(input) || !isValidInput(input)) 
        {
            cout << LIGHT_CYAN << "Please choose a valid move!" << RESET << endl;
            printDirections();
            cin >> in;
            input = atoi(in.c_str());
        }

        board[input] = 'X';

        cout << "Board:" << endl << endl;
        print_board();

        GameDecision winner = checkForWinners(board);

        if (winner == player)
        {
            cout << LIGHT_GREEN << "You win!\n" << RESET << endl;
            noWinnersYet = false;;
        }
        else if (isGameADraw(board))
        {
            cout << LIGHT_PURPLE << "It is a draw guys!" << RESET << endl;
            noWinnersYet = false;
        }
        else 
        {
            minimax(false, board, 0); //false indicates it is computer's turn
            board[positionMin] = 'O';

            cout << "Computer is making a move..." << endl;
            cout << "And computer puts a O at " << positionMin << endl;
            print_board();

            if (checkForWinners(board) == computer)
            {
                cout << LIGHT_RED << "Computer wins!" << RESET << endl;
                noWinnersYet = false;
            }
        }
    }
}

bool isValidInput(int input)
{
    return (input >= 1 && input <= 9);
}

void print_board()
{
    for (int i = 1; i < MAX_BOARD_SIZE; i++)
    {   
        if (board[i] == 'X')
            cout << LIGHT_GREEN << 'X' << RESET << " ";
        else if (board[i] == 'O')
            cout << RED << 'O' << RESET << " ";
        else
            cout << board[i] << " ";
        if (i % 3 == 0)
            cout << "\n";
    }
    cout << endl;
}

void printDirections()
{
    cout << "\tPress 1 - 9 for placement of your piece." << endl;
    cout << "\tThe board is laid out in the following manner:" << endl;
    cout << "\t\t\t";
    cout << LIGHT_PURPLE;

    for (int i = 1; i < MAX_BOARD_SIZE; i++)
    {   
        cout << i << " ";
        if (i % 3 == 0)
            cout << "\n\t\t\t";
    }
    cout << RESET << endl;
}

bool checkForConnectingLines(char ch)
{
    return (
        (board[1] == ch && board[2] == ch && board[3] == ch) ||
        (board[4] == ch && board[5] == ch && board[6] == ch) ||
        (board[7] == ch && board[8] == ch && board[9] == ch) ||
        (board[1] == ch && board[4] == ch && board[7] == ch) ||
        (board[2] == ch && board[5] == ch && board[8] == ch) ||
        (board[3] == ch && board[6] == ch && board[9] == ch) ||
        (board[1] == ch && board[5] == ch && board[9] == ch) ||
        (board[3] == ch && board[5] == ch && board[7] == ch));
}

GameDecision checkForWinners(char board[])
{
    GameDecision winResults = allelse;
    
    if (checkForConnectingLines('X')) 
    {
        winResults = player;
    }
    else if(checkForConnectingLines('O')) 
    {
        winResults = computer;
    }
    
    return winResults;
}

int minimax(bool playerTurn, char board[], int n)
{
    int gain = 0;
    int max = -INFINITY;
    int min = INFINITY;

    GameDecision whoWins = checkForWinners(board);
    if (whoWins == player || whoWins == computer || isGameADraw(board))
        return whoWins;

    for (int i = 1; i < MAX_BOARD_SIZE; i++)
    {
        if(isPositionEmpty(i))
        {
            board[i] = playerTurn ? 'X' : 'O'; //place 'X' if it is player turn, else 'O'
            gain = minimax(!playerTurn, board, n + 1);
            board[i] = '_';

            if (playerTurn)
            {
                if (gain > max)
                {
                    max = gain;
                    if (n == 0)
                    {
                        positionMax = i;
                    }
                }
            } else
            {
                if (gain < min)
                {
                    min = gain;
                    if (n == 0)
                    {
                        positionMin = i;
                    }
                }
            }
        }
    }
    return (playerTurn) ? max : min; 
}

bool isPositionEmpty(int position)
{
    return (board[position] == '_');
}

bool isGameADraw(char board[])
{
    GameDecision winResults = checkForWinners(board);
    bool boardIsFilled = true;
    
    for (int i = 1; i < MAX_BOARD_SIZE; i++)
    {
        if (isPositionEmpty(i))
        {
            boardIsFilled = false;
            break;
        }
    }
    return (winResults == allelse && boardIsFilled);
}