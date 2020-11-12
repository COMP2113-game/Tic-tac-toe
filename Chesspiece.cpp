#include "Chesspiece.h"
using namespace std;

Chesspiece::Chesspiece(){
    pieceLabel = ' ';
}

Chesspiece::Chesspiece(char piece){
    setPieceLabel(piece);
}

const char Chesspiece::getPieceLabel()
{
    return pieceLabel;
}

void Chesspiece::setPieceLabel(char Chesspiece){
    if (Chesspiece == 'X' || Chesspiece == 'O' || Chesspiece == '_')
    {
        pieceLabel = Chesspiece;
    } else {
        pieceLabel = ' ';
    }
}

