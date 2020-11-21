#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Chesspiece.h"
typedef enum {player = 1, robot = -1, allelse = 0} GameDecision;

class Game : public Board {
public:
    Game();
    void printManual();
    void start();
private:
    bool gameContinue;
    int getPositionMax();
    int getPositionMin();
    int randomMove();
    int minimax(bool playerTurn, int n);
    bool isGameADraw();
    bool checkForConnectingLines(Chesspiece chess);
    GameDecision checkForWinner();
    void saveGame();
    void readGame();
};
#endif
