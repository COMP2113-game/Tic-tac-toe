//Author:Chen Yulin & Wang Manlin
//File: Chesspiece.h

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

class Chesspiece {
public:
    Chesspiece();
    Chesspiece(char piece);
    const char getPieceLabel();
    void setPieceLabel(char piece);
private:
    char pieceLabel;
};

#endif
