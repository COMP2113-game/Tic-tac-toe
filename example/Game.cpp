#include "Game.h"

#define INFINITY 1073741824
static int positionMax, positionMin;

Game::Game(){}

int Game::getPositionMax()
{
    return positionMax;
}

int Game::getPositionMin()
{
    return positionMin;
}

int Game::minimax(bool playerTurn, int n)
{
    int gain = 0;
    int max = -INFINITY;
    int min = INFINITY;

    GameDecision whoWins = checkForWinners();
    if (whoWins == player || whoWins == computer || isGameADraw())
        return whoWins;

    for (int i = 1; i < boardSize(); i++)
    {
        if(isPositionEmpty(i))
        {
            char pieceLabel = playerTurn ? 'X' : 'O'; //place 'X' if it is player turn, else 'O'
            chesspiece piece(pieceLabel);
            insertIntoPosition(i, piece);
            
            gain = minimax(!playerTurn, n + 1);
            
            piece.setPieceLabel('_');
            insertIntoPosition(i, piece);

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

bool Game::isGameADraw()
{
    GameDecision winResults = checkForWinners();
    bool sFilled = true;
    
    for (int i = 1; i < boardSize(); i++)
    {
        if (isPositionEmpty(i))
        {
            sFilled = false;
            break;
        }
    }
    return (winResults == allelse && sFilled);
}

bool Game::checkForConnectingLines(chesspiece chess)
{
    char ch = chess.getPieceLabel();

     return (
        (getPieceAtPosition(1).getPieceLabel() == ch && getPieceAtPosition(2).getPieceLabel() == ch && getPieceAtPosition(3).getPieceLabel() == ch) ||
        (getPieceAtPosition(4).getPieceLabel() == ch && getPieceAtPosition(5).getPieceLabel() == ch && getPieceAtPosition(6).getPieceLabel() == ch) ||
        (getPieceAtPosition(7).getPieceLabel() == ch && getPieceAtPosition(8).getPieceLabel() == ch && getPieceAtPosition(9).getPieceLabel() == ch) ||
        (getPieceAtPosition(1).getPieceLabel() == ch && getPieceAtPosition(4).getPieceLabel() == ch && getPieceAtPosition(7).getPieceLabel() == ch) ||
        (getPieceAtPosition(2).getPieceLabel() == ch && getPieceAtPosition(5).getPieceLabel() == ch && getPieceAtPosition(8).getPieceLabel() == ch) ||
        (getPieceAtPosition(3).getPieceLabel() == ch && getPieceAtPosition(6).getPieceLabel() == ch && getPieceAtPosition(9).getPieceLabel() == ch) ||
        (getPieceAtPosition(1).getPieceLabel() == ch && getPieceAtPosition(5).getPieceLabel() == ch && getPieceAtPosition(9).getPieceLabel() == ch) ||
        (getPieceAtPosition(3).getPieceLabel() == ch && getPieceAtPosition(5).getPieceLabel() == ch && getPieceAtPosition(7).getPieceLabel() == ch));
}

GameDecision Game::checkForWinners()
{
    GameDecision winResults = allelse;
    chesspiece piece('X');
    chesspiece anotherpiece('O');

    if (checkForConnectingLines(piece.getPieceLabel())) 
    {
        winResults = player;
    }
    else if(checkForConnectingLines(anotherpiece.getPieceLabel())) 
    {
        winResults = computer;
    } 
    return winResults;
}