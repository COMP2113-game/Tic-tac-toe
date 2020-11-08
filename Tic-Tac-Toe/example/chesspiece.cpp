#include "chesspiece.h"
using namespace std;

chesspiece::chesspiece(){
    pieceLabel = ' ';    
}

chesspiece::chesspiece(char piece){
    setPieceLabel(piece);
}

const char chesspiece::getPieceLabel()
{
    return pieceLabel;
}

void chesspiece::setPieceLabel(char chesspiece){
    if (chesspiece == 'X' || chesspiece == 'O' || chesspiece == '_')
    {
        pieceLabel = chesspiece;
    } else {
        pieceLabel = ' ';
    }
}