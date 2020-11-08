#include <cassert>
#include <iostream>
#include "chesspiece.h"
using namespace std;

void testInit();
void TestInitWithPiece();
void testGetAndSetPiece();

int main()
{
    cout << "Test initialization for chesspiece\n";
    testInit();
    cout << "Passed initialization for chesspiece\n\n";

    cout << "Test init with piece from chesspiece\n";
    TestInitWithPiece();
    cout << "Passed init with piece from chesspiece\n\n";

    cout << "test setting to and getting piece from chesspiece\n";
    testGetAndSetPiece();
    cout << "Passed setting to and getting piece from chesspiece\n\n";
}

void testInit()
{
    chesspiece *piece = new chesspiece();
    assert(piece != NULL);
    delete piece;

    chesspiece anotherpiece;
    assert (anotherpiece.getPieceLabel() == ' ');
}

void TestInitWithPiece()
{
    chesspiece pieceX('X');
    assert (pieceX.getPieceLabel() == 'X');
    chesspiece pieceO('O');
    assert (pieceO.getPieceLabel() == 'O');
    chesspiece invalidPieceShouldBeEmpty('Z');
    assert (invalidPieceShouldBeEmpty.getPieceLabel() == ' ');
}

void testGetAndSetPiece()
{
    chesspiece piece;
    piece.setPieceLabel('X');
    assert(piece.getPieceLabel() == 'X');
    piece.setPieceLabel('O');
    assert(piece.getPieceLabel() == 'O');
    piece.setPieceLabel('_');
    assert(piece.getPieceLabel() == '_');
    piece.setPieceLabel('R');
    assert(piece.getPieceLabel() == ' ');
    piece.setPieceLabel('Z');
    assert(piece.getPieceLabel() != 'X' && piece.getPieceLabel() != 'O' && piece.getPieceLabel() != '_');
}
