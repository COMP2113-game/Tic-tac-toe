#include <iostream>
#include <string>

/* Game and chesspiece files */
#include "Game.h"
#include "chesspiece.h"
using namespace std;

// sets the console output to different colors 
#define RED "\033[22;31m" 
#define RESET "\033[0m" //resets to console output to default color
#define LIGHT_RED "\033[01;31m"
#define LIGHT_GREEN "\033[01;32m"
#define LIGHT_PURPLE "\033[01;35m"
#define LIGHT_CYAN "\033[01;36m"

void printDirections(Game &game);
void startGame(Game &game);

int main()
{
    Game newGame;
    printDirections(newGame);

    cout << "The board is empty now." << endl;
    newGame.print_board();

    cout << RED << "\n\nAs a guest, you can start first! You will be X." << RESET << endl;
    startGame(newGame);

    return 0;
}

void printDirections(Game &game)
{
    int gameBoardSize = game.boardSize();
    cout << "\tPress 1 - 9 for placement of your piece." << endl;
    cout << "\tThe board is laid out in the following manner:" << endl;
    cout << "\t\t\t";
    cout << LIGHT_PURPLE;

    for (int i = 1; i < gameBoardSize; i++)
    {   
        cout << i << " ";
        if (i % 3 == 0)
            cout << "\n\t\t\t";
    }
    cout << RESET << endl;
}

void startGame(Game &game)
{
    string in = "";
    bool noWinnersYet = true;

    for(int i = 1; i < game.boardSize() && noWinnersYet; i++)
    {
        cin >> in;
        int input = atoi(in.c_str());

        chesspiece playerPiece('X');
        chesspiece comPiece('O');

        while  (!game.isValidPosition(input) || !game.isPositionEmpty(input)) 
        {
            cout << LIGHT_CYAN << "Please choose a valid move!" << RESET << endl;
            printDirections(game);
            cin >> in;
            input = atoi(in.c_str());
        }

        game.insertIntoPosition(input, playerPiece);

        cout << "Board:\n\n";
        game.print_board();

        GameDecision winner = game.checkForWinners();

        if (winner == player)
        {
            cout << LIGHT_GREEN << "You win!\n" << RESET << endl;
            noWinnersYet = false;;
        }
        else if (game.isGameADraw())
        {
            cout << LIGHT_PURPLE << "It is a draw guys!" << RESET << endl;
            noWinnersYet = false;
        }
        else 
        {
            game.minimax(false, 0); //false indicates it is computer's turn
            game.insertIntoPosition(game.getPositionMin(), comPiece);

            cout << "Computer is making a move..." << endl;
            cout << "And computer puts a O at " << game.getPositionMin() << endl;
            game.print_board();

            if (game.checkForWinners() == computer)
            {
                cout << LIGHT_RED << "Computer wins!" << RESET << endl;
                noWinnersYet = false;
            }
        }
    }
}