#include "Chesspiece.h"

// Chesspiece
// Purpose:     Initialize the pieceLabel as the blank space
// Arguments:   None
// Returns:     None
Chesspiece::Chesspiece(){
    pieceLabel = ' ';
}

// getPieceLabel
// Purpose:     Get the pieceLabel of the Chesspiece type variable
// Arguments:   None
// Returns:     pieceLabel (char)
const char Chesspiece::getPieceLabel()
{
    return pieceLabel;
}

// setPieceLabel
// Purpose:     Set the pieceLabel as the argument
// Arguments:   piece (char)
// Returns:     None
void Chesspiece::setPieceLabel(char piece){
    if (piece == 'X' || piece == 'O' || piece == '_')
    {
        pieceLabel = piece;
    } else {
        pieceLabel = ' ';
    }
}

