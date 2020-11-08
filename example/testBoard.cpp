#include "Board.h"
#include <cassert>
#include <iostream>
using namespace std;

void testInsertIntoBoard();
void testIsEmptyPosition();
void testCanRemovePosition();
void testCheckPositionReturnsValidPiece();
void testCheckIsValidPosition();
void testCheckIsEmptyPositionShouldReturnFalse();

int main()
{
    cout << "Testing insert into board\n";
    testInsertIntoBoard();
    cout << "Passed insert into board\n\n";

    cout << "Testing isEmptyPosition method:\n";
    testIsEmptyPosition();
    cout << "Passed isEmptyPosition method\n\n";

    cout << "Testing removing piece from board method:\n";
    testCanRemovePosition();
    cout << "Passed testCanRemovePosition\n\n";

    cout << "Testing getPieceAtPosition method:\n";
    testCheckPositionReturnsValidPiece();
    cout << "Passed getPieceAtPosition test \n\n";

    cout << "Testing isValidPosition method:\n";
    testCheckIsValidPosition();
    cout << "Passed isValidPosition test\n\n";

    cout << "Testing isEmptyPosition with non empty position\n";
    testCheckIsEmptyPositionShouldReturnFalse();
    cout << "Passed isEmptyPosition with non empty position\n\n";

    return 0;
}

void testInsertIntoBoard()
{
    chesspiece piece('X');
    Board board;
    for (int i = 1; i < board.boardSize(); i++)
    {   
        assert(board.insertIntoPosition(i, piece));
    }
    assert(false == board.insertIntoPosition(15000, piece));

    chesspiece newPiece('T');
    assert(false == board.insertIntoPosition(3, newPiece));
}

void testIsEmptyPosition()
{
    Board board;
    chesspiece piece('X');
    board.insertIntoPosition(1, piece);
    assert (board.isPositionEmpty(1) == false);
    assert (board.isPositionEmpty(2) == true);
}

void testCanRemovePosition()
{
    Board board;
    chesspiece piece('O');
    for (int i = 1; i < board.boardSize(); i++)
        board.insertIntoPosition(i, piece);
    assert (board.removePosition(3) == true);
    assert (board.removePosition(10) == false);
    assert (board.removePosition(0) == false);
}

void testCheckPositionReturnsValidPiece()
{
    Board board;
    chesspiece piece('X');

    for (int i = 1; i < board.boardSize(); i++)
        board.insertIntoPosition(i, piece);

    chesspiece pieceShouldBeX = board.getPieceAtPosition(5);
    assert (pieceShouldBeX.getPieceLabel() == 'X');
    chesspiece pieceShouldNotBeO = board.getPieceAtPosition(9);
    assert (pieceShouldNotBeO.getPieceLabel() != 'O');  
    chesspiece pieceShouldBeEmpty = board.getPieceAtPosition(100);
    assert (pieceShouldBeEmpty.getPieceLabel() == ' ');
}

void testCheckIsValidPosition()
{
    Board board;
    assert (board.isValidPosition(9) == true);
    assert (board.isValidPosition(1) == true);
    assert (board.isValidPosition(0) == false);
    assert (board.isValidPosition(10000) == false);
}

void testCheckIsEmptyPositionShouldReturnFalse()
{
    Board board;
    chesspiece piece('X');
    board.insertIntoPosition(1, piece);
    assert (board.isPositionEmpty(1) == false);
}
