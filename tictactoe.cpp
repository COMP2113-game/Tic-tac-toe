/*******************************************************************************
 * Main Program                                                                *
 ******************************************************************************/

#include <iostream>
#include <string>
#include <fstream>

#include "Game.h"
#include "Chesspiece.h"
using namespace std;

int main()
{
    Game game;
    game.printManual();
    game.start();
    return 0;
}

