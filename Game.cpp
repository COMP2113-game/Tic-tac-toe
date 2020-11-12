#include "Game.h"
#include "Chesspiece.h"
#include <iostream>
#include <fstream>

#define LIGHT_PURPLE "\033[01;35m"
#define RED "\033[22;31m"
#define RESET "\033[0m"
#define LIGHT_GREEN "\033[01;32m"
#define INFINITY 1073741824
#define MAX_BOARD_SIZE 10
using namespace std;

static int positionMax, positionMin;
Chesspiece player_piece('X');
Chesspiece robot_piece('O');
Game::Game(){
    gameContinue = true;
}

int Game::getPositionMax()
{
    return positionMax;
}

int Game::getPositionMin()
{
    return positionMin;
}

// start
// Purpose:     Allow user to choose between starting a game and continue from the last game
// Arguments:   bool playerTurn, int n
// Returns:     (playerTurn) ? max : min
int Game::minimax(bool playerTurn, int n)
{
    int gain = 0;
    int max = -INFINITY;
    int min = INFINITY;
    
    GameDecision whoWins = checkForWinners();
    if (whoWins == player || whoWins == computer || isGameADraw())
        return whoWins;
    
    for (int i = 1; i < boardSize(); i++)
    {
        if(isEmpty(i))
        {
            char pieceLabel = playerTurn ? 'X' : 'O'; //place 'X' if it is player turn, else 'O'
            Chesspiece piece(pieceLabel);
            insertToBoard(i, piece);
            
            gain = minimax(!playerTurn, n + 1);
            
            piece.setPieceLabel('_');
            insertToBoard(i, piece);
            
            if (playerTurn)
            {
                if (gain > max)
                {
                    max = gain;
                    if (n == 0)
                    {
                        positionMax = i;
                    }
                }
            } else
            {
                if (gain < min)
                {
                    min = gain;
                    if (n == 0)
                    {
                        positionMin = i;
                    }
                }
            }
        }
    }
    return (playerTurn) ? max : min;
}

bool Game::isGameADraw()
{
    GameDecision winResults = checkForWinners();
    bool sFilled = true;
    
    for (int i = 1; i < boardSize(); i++)
    {
        if (isEmpty(i))
        {
            sFilled = false;
            break;
        }
    }
    return (winResults == allelse && sFilled);
}

bool Game::checkForConnectingLines(Chesspiece chess)
{
    char ch = chess.getPieceLabel();
    
    return (
            (getPieceAtPos(1).getPieceLabel() == ch && getPieceAtPos(2).getPieceLabel() == ch && getPieceAtPos(3).getPieceLabel() == ch) ||
            (getPieceAtPos(4).getPieceLabel() == ch && getPieceAtPos(5).getPieceLabel() == ch && getPieceAtPos(6).getPieceLabel() == ch) ||
            (getPieceAtPos(7).getPieceLabel() == ch && getPieceAtPos(8).getPieceLabel() == ch && getPieceAtPos(9).getPieceLabel() == ch) ||
            (getPieceAtPos(1).getPieceLabel() == ch && getPieceAtPos(4).getPieceLabel() == ch && getPieceAtPos(7).getPieceLabel() == ch) ||
            (getPieceAtPos(2).getPieceLabel() == ch && getPieceAtPos(5).getPieceLabel() == ch && getPieceAtPos(8).getPieceLabel() == ch) ||
            (getPieceAtPos(3).getPieceLabel() == ch && getPieceAtPos(6).getPieceLabel() == ch && getPieceAtPos(9).getPieceLabel() == ch) ||
            (getPieceAtPos(1).getPieceLabel() == ch && getPieceAtPos(5).getPieceLabel() == ch && getPieceAtPos(9).getPieceLabel() == ch) ||
            (getPieceAtPos(3).getPieceLabel() == ch && getPieceAtPos(5).getPieceLabel() == ch && getPieceAtPos(7).getPieceLabel() == ch));
}

GameDecision Game::checkForWinners()
{
    GameDecision winResults = allelse;
    Chesspiece piece('X');
    Chesspiece anotherpiece('O');
    
    if (checkForConnectingLines(piece.getPieceLabel()))
    {
        winResults = player;
    }
    else if(checkForConnectingLines(anotherpiece.getPieceLabel()))
    {
        winResults = computer;
    }
    return winResults;
}

// start
// Purpose:     Allow user to choose between starting a game and continue from the last game
// Arguments:   None
// Returns:     None
void Game::printManual()
{
    int size = boardSize();
    cout << "Enter \"CONT\" to continue playing the last saved game, enter \"NEW\" to start a new game"<<endl;
    string cmd;
    cin >> cmd;
    bool validInput = 0;
    cout << "Please familiarize yourself with the laid out of the board:\n" << endl;
    cout << "\t\t\t";
    cout << LIGHT_PURPLE;
    for (int i = 1; i < boardSize(); i++)
    {
        cout << i << " ";
        if (i % 3 == 0)
            cout << "\n\t\t\t";
    }
    cout << RESET;
    while (!validInput){
        if (cmd == "CONT"){
            validInput = 1;
            readGame();
        }
        else if (cmd == "NEW"){
            validInput = 1;
            cout << LIGHT_PURPLE << "\nChoose the level of your opponent. Enter 1 or 2: " << RESET << endl;
            cout << "\t1. Easy \t 2. Impossible" << endl;
            cout <<  LIGHT_PURPLE << "\nEnter 1 - 9 from your keyboard to place your move: "<< RESET <<endl;
        }
        else {
            cout << "Please enter a valid input \n"
            "Enter \"CONTINUE\" to continue playing the last saved game, enter \"NEW\" to start a new game"<<endl;
            cin >> cmd;
        }
    }
}

// start
// Purpose:     Start the game
// Arguments:   None
// Returns:     None
void Game::start(){
    cout << "You will start first! You will be \"X\":" << endl;
    gameContinue = true;
    string in;
    // loop until there is a winner or user save the current game
    while(gameContinue)
    {
        cout << "It's your turn now, "
        "enter \"SAVE\" to save the current game and exit\n"
        "Enter 1-9 to place your move: "<<endl;
        
        // get user input
        cin >> in;
        int input = atoi(in.c_str());
        if (in=="SAVE"){
            // save current game
            saveGame();
            gameContinue = false;
            continue;
        }
        
        // check if user input is valid
        while  (!isValidPos(input) || !isEmpty(input))
        {
            cout << RED << "Please choose a valid move!" << RESET << endl;
            cin >> in;
            input = atoi(in.c_str());
        }
        insertToBoard(input, player_piece);
        
        cout << "Board:\n";
        print_board();
        
        GameDecision winner = checkForWinners();
        
        if (winner == player)
        {
            cout << LIGHT_PURPLE << "You win!\n" << RESET << endl;
            gameContinue = false;
        }
        else if (isGameADraw())
        {
            cout << LIGHT_PURPLE << "It is a draw guys!" << RESET << endl;
            gameContinue = false;
        }
        else
        {   // Impossible level robot, minimax agent, please modify and add random agent here
            minimax(false, 0); //false indicates it is computer's turn
            insertToBoard(getPositionMin(), robot_piece);
            
            cout << "Robot is making a move..." << endl;
            cout << "And robot puts a O at " << getPositionMin() << endl;
            print_board();
            
            if (checkForWinners() == computer)
            {
                cout << LIGHT_PURPLE << "Robot wins!" << RESET << endl;
                gameContinue = false;
            }
        }
    }
}

// saveGame
// Purpose:     Save the current game for reload
// Arguments:   None
// Returns:     None
void Game::saveGame()
{
    ofstream myfile ("board.txt");
    if (myfile.is_open()){
        for (int i = 1; i < MAX_BOARD_SIZE; i++)
        {
            Chesspiece pieceAtPositioni = getPieceAtPos(i);
            if (pieceAtPositioni.getPieceLabel() == 'X')
                myfile << 'X' << " ";
            else if (pieceAtPositioni.getPieceLabel() == 'O')
                myfile << 'O' << " ";
            else
                myfile << pieceAtPositioni.getPieceLabel() << " ";
            if (i % 3 == 0)
                myfile << "\n";
        }
        myfile.close();
    }
    else cout << "Unable to save the game";
}

// readGame
// Purpose:     Reload the last saved game
// Arguments:   None
// Returns:     None
void Game::readGame(){
    string line;
    ifstream myfile ("board.txt");
    if (myfile.is_open())
    {
        char piece;
        int position = 1;
        while ( myfile >> piece ){
            if (piece == 'X') {
                insertToBoard(position, player_piece);
            }
            else if (piece == 'O') {
                insertToBoard(position, robot_piece);
            }
            position ++;
        }
        cout << "\nBoard loaded from the last saved game:\n";
        print_board();
        myfile.close();
    }
    
    else cout << "Unable to open file";
}
