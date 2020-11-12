//Author:Chen Yulin & Wang Manlin
//File: Chesspiece.h

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

class Chesspiece {
public:
    Chesspiece();
    const char getPieceLabel();
    void setPieceLabel(char Chesspiece);
private:
    char pieceLabel;
};

#endif
