#include "Board.h"
#include <iostream>
using namespace std;
// sets the console output to different colors 
#define RED "\033[22;31m" 
#define RESET "\033[0m" 
#define LIGHT_GREEN "\033[01;32m"
#define BOARD_SIZE 10

Board::Board()
{
    board = new char(BOARD_SIZE);
    for (int i = 1; i < BOARD_SIZE; ++i)
    {
        board[i] = '_';
    }    
}
Board::~Board()
{
    delete [] board;
    board = NULL;
}

// boardSize
// Purpose:     get the size of the board
// Arguments:   None
// Returns:     board size + 1
const int Board::boardSize()
{
    return BOARD_SIZE;
}

// insertToBoard
// Purpose:     place user's move into the board at the specified position
// Arguments:   position (int), input specifying player/robot (Chesspiece)
// Returns:     If succefully insert or not (bool)
bool Board::insertToBoard(int pos, Chesspiece input)
{
    bool insert = false;
    if (isValidPos(pos))
    {
        board[pos] = input.getPieceLabel();
        insert = true;
    }
    return insert;
}

// isEmpty
// Purpose:     check if the board is empty at the input position
// Arguments:   position (int)
// Returns:     If input position is empty or not (bool)
bool Board::isEmpty(int pos)
{
    return (isdigit(board[pos]));
}

// removePos
// Purpose:     remove piece at specified position if not empty
// Arguments:   position (int)
// Returns:     If input position is empty after removal (bool)
bool Board::removePos(int pos)
{
    bool isPieceRemoved = false;
    if (isValidPos(pos))
    {
        isPieceRemoved = isdigit(board[pos]);
    }
    return isPieceRemoved;
}

// getPieceAtPos
// Purpose:     get the chesspiece at the specified position
// Arguments:   position (int)
// Returns:     chesspiece at posision (Chesspiece)
Chesspiece Board::getPieceAtPos(int pos)
{
    Chesspiece piece;
    if (isValidPos(pos))
    {
        piece.setPieceLabel(board[pos]);
    }
    return piece;
}

// isValidPos
// Purpose:     check if the input position is valid
// Arguments:   position (int)
// Returns:     if the position is valid (bool)
bool Board::isValidPos(int pos)
{
    return (pos >= 1 && pos <= 9);
}

// print_board
// Purpose:     print the current chess board
// Arguments:   None
// Returns:     None
void Board::print_board()
{
    for (int i = 1; i < BOARD_SIZE; i++)
    {   
        Chesspiece piece = getPieceAtPos(i);
        if (piece.getPieceLabel() == 'X')
            cout << LIGHT_GREEN << 'X' << RESET << " ";
        else if (piece.getPieceLabel() == 'O')
            cout << RED << 'O' << RESET << " ";
        else
            cout << i << " ";
        if (i % 3 == 0)
            cout << "\n";
    }
    cout << endl;
}

// // isValidInput
// // Purpose:     print the current chess board
// // Arguments:   None
// // Returns:     None
// bool Board::isValidInput(Chesspiece input)
// {
//     char c = input.getPieceLabel();
//     return (c == 'X' || c == 'O' || c == '_');
// }