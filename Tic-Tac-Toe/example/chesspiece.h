/*  Author:Zhia Chong
    File: chesspiece.h
*/
#ifndef CHESSPIECE_H
#define CHESSPIECE_H
class chesspiece {
    public:
        chesspiece();
        chesspiece(char piece);
        const char getPieceLabel();
        void setPieceLabel(char chesspiece);
    private:
        char pieceLabel;
};

#endif