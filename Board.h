#ifndef BOARD_H
#define BOARD_H
#include "Chesspiece.h"
class Board {
  public:
    Board();
    ~Board();
    bool insertIntoPosition(int position, Chesspiece input);
    bool isPositionEmpty(int position);
    bool removePosition(int position);
    Chesspiece getPieceAtPosition(int position);
    const int boardSize();
    bool isValidPosition(int position);
    void print_board();
    bool isValidInput(Chesspiece input);
  protected:  
    char *board;
};
#endif