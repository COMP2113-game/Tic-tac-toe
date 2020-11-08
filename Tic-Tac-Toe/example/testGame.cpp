#include "Game.h"
#include "chesspiece.h"
#include <iostream>
#include <cassert>
using namespace std;


void testNotADrawGame();
void testisGameADrawShouldReturnTrueForADrawGame();
void testConnectingLinesShouldReturnFalse();
void testConnectingLinesShouldReturnTrue();
void testcheckWinnersShouldReturnComputer();
void testcheckWinnerShouldReturnPlayer();
void testCheckWinnerShouldReturnAllElse();
void testminiMaxShouldReturn5();

int main()
{
    cout << "Test for isGameADraw method\n";
    testNotADrawGame();
    testisGameADrawShouldReturnTrueForADrawGame();
    cout << "Passed test\n\n";

    cout << "Test for checkForConnectingLines method\n";
    testConnectingLinesShouldReturnFalse();
    testConnectingLinesShouldReturnTrue();
    cout << "Passed test\n\n";

    cout << "Test for checkForWinners method\n";
    cout << "Checking winner should be computer\n";
    testcheckWinnersShouldReturnComputer();
    cout << "Passed test\n\n";

    cout << "Test for checkForWinners method\n";
    cout << "Checking winner should be player\n";
    testcheckWinnerShouldReturnPlayer();
    cout << "Passed test\n\n";

    cout << "Test for checkForWinners method\n";
    cout << "Checking winner should be all else\n";
    testCheckWinnerShouldReturnAllElse();
    cout << "Passed test\n\n";

    cout << "Test for minMax method\n";
    cout << "Should return 5 for optimal step if player puts anything but 5 in the board\n";
    testminiMaxShouldReturn5();
    cout << "Passed test\n\n";

}

void testNotADrawGame()
{
    Game game;
    assert (game.isGameADraw() == false);
}

void testConnectingLinesShouldReturnTrue()
{
    Game game;
    chesspiece X('X');
    chesspiece O('O');
    
    game.insertIntoPosition(1, X);
    game.insertIntoPosition(2, X);
    game.insertIntoPosition(3, X);
    assert (game.checkForConnectingLines(X) == true);

    Game diagonalLineGame;
    diagonalLineGame.insertIntoPosition(1, X);
    diagonalLineGame.insertIntoPosition(5, X);
    diagonalLineGame.insertIntoPosition(9, X);
    assert (diagonalLineGame.checkForConnectingLines(X) == true);

    Game verticalLineGame;
    verticalLineGame.insertIntoPosition(3, O);
    verticalLineGame.insertIntoPosition(6, O);
    verticalLineGame.insertIntoPosition(9, O);
    assert (verticalLineGame.checkForConnectingLines(O) == true);
}

void testisGameADrawShouldReturnTrueForADrawGame()
{
    Game game;
    chesspiece X('X');
    chesspiece O('O');
    for (int i = 1; i < game.boardSize(); i++)
    {
        if (i % 4 == 0 || i == 3 || i == 5)
            game.insertIntoPosition(i, X);
        else
            game.insertIntoPosition(i, O);
    }
    assert (game.isGameADraw() == true);
}

void testConnectingLinesShouldReturnFalse()
{
    Game game;
    chesspiece X('X');
    chesspiece O('O');
    for (int i = 1; i < game.boardSize(); i++)
    {
        if (i % 4 == 0 || i == 3 || i == 5)
            game.insertIntoPosition(i, X);
        else
            game.insertIntoPosition(i, O);
    }

    assert (game.checkForConnectingLines(X) == false);

}

void testcheckWinnersShouldReturnComputer()
{
    Game game;
    chesspiece O('O');

    game.insertIntoPosition(1, O);
    game.insertIntoPosition(2, O);
    game.insertIntoPosition(3, O);

    GameDecision winner = game.checkForWinners();
    assert (winner == computer);
}

void testcheckWinnerShouldReturnPlayer()
{
    Game game;
    chesspiece X('X');

    game.insertIntoPosition(1, X);
    game.insertIntoPosition(2, X);
    game.insertIntoPosition(3, X);

    GameDecision winner = game.checkForWinners();
    assert (winner == player);
}

void testCheckWinnerShouldReturnAllElse()
{
    Game game;
    chesspiece O('O');
    chesspiece X('X');

    game.insertIntoPosition(1, O);
    game.insertIntoPosition(2, O);
    game.insertIntoPosition(3, X);

    GameDecision winner = game.checkForWinners();
    assert (winner == allelse);
}

void testminiMaxShouldReturn5()
{
    Game game;
    chesspiece X('X');

    game.insertIntoPosition(1, X);
    game.minimax(false, 0); //false indicates computer's turn
    assert (game.getPositionMin() == 5); //positionMin is the next step for computer 
}