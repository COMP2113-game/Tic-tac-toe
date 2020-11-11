#ifndef BOARD_H
#define BOARD_H
#include "Chesspiece.h"
class Board {
  public:
    Board();
    ~Board();
    bool insertToBoard(int pos, Chesspiece input);
    bool isEmpty(int pos);
    bool removePos(int pos);
    Chesspiece getPieceAtPos(int pos);
    const int boardSize();
    bool isValidPos(int pos);
    void print_board();
  
  protected:  
    char *board;
};
#endif