/*******************************************************************************
 * Main Program                                                                *
 ******************************************************************************/

#include <iostream>
#include <string>

#include "Game.h"
#include "Chesspiece.h"
using namespace std;

int main()
{
    Game game;
    game.printManual();

    cout << "The board is empty now." << endl;
    game.print_board();
    game.start();

    return 0;
}