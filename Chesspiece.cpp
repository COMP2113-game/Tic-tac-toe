#include "Chesspiece.h"
using namespace std;

Chesspiece::chesspiece(){
    pieceLabel = ' ';
}

Chesspiece::chesspiece(char piece){
    setPieceLabel(piece);
}

const char Chesspiece::getPieceLabel()
{
    return pieceLabel;
}

void Chesspiece::setPieceLabel(char chesspiece){
    if (chesspiece == 'X' || chesspiece == 'O' || chesspiece == '_')
    {
        pieceLabel = chesspiece;
    } else {
        pieceLabel = ' ';
    }
}

