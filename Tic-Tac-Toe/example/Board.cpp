#include "Board.h"
#include <iostream>
using namespace std;
// sets the console output to different colors 
#define RED "\033[22;31m" 
#define RESET "\033[0m" //resets to console output to default color
#define GREY "\033[22;37m"
#define LIGHT_RED "\033[01;31m"
#define LIGHT_GREEN "\033[01;32m"
#define LIGHT_PURPLE "\033[01;35m"
#define LIGHT_CYAN "\033[01;36m"

#define MAX_BOARD_SIZE 10
Board::Board()
{
    board = new char(MAX_BOARD_SIZE);
    for (int i = 1; i < MAX_BOARD_SIZE; i++)
    {
        board[i] = '_';
    }    
}
Board::~Board()
{
    delete [] board;
    board = NULL;
}

const int Board::boardSize()
{
    return MAX_BOARD_SIZE;
}

bool Board::insertIntoPosition(int position, chesspiece input)
{
    bool success = false;
    if (isValidPosition(position) && isValidInput(input))
    {
        board[position] = input.getPieceLabel();
        success = true;
    }
    return success;
}

bool Board::isPositionEmpty(int position)
{
    return (board[position] == '_');
}

bool Board::removePosition(int position)
{
    bool isPieceRemoved = false;
    if (isValidPosition(position))
    {
        board[position] = '_';
        isPieceRemoved = true;
    }
    return isPieceRemoved;
}

chesspiece Board::getPieceAtPosition(int position)
{
    chesspiece piece;
    if (isValidPosition(position))
    {
        piece.setPieceLabel(board[position]);
    }
    return piece;
}

bool Board::isValidPosition(int position)
{
    return (position >= 1 && position <= 9);
}

void Board::print_board()
{
    for (int i = 1; i < MAX_BOARD_SIZE; i++)
    {   
        chesspiece pieceAtPositioni = getPieceAtPosition(i);
        if (pieceAtPositioni.getPieceLabel() == 'X')
            cout << LIGHT_GREEN << 'X' << RESET << " ";
        else if (pieceAtPositioni.getPieceLabel() == 'O')
            cout << RED << 'O' << RESET << " ";
        else
            cout << pieceAtPositioni.getPieceLabel() << " ";
        if (i % 3 == 0)
            cout << "\n";
    }
    cout << endl;
}

bool Board::isValidInput(chesspiece input)
{
    char c = input.getPieceLabel();
    return (c == 'X' || c == 'O' || c == '_');
}