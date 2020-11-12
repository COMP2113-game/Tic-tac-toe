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
    
    ifstream fin ("board.txt");
    if (!fin.fail())
    {
        fin.close();
        game.start();
    }
    else
    {
    cout << "The board is empty now." << endl;
    game.print_board();
    game.start();
    }
    
    return 0;
}

