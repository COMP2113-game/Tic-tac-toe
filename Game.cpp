#include "Game.h"
#include "Chesspiece.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <limits>
#include <cstdlib>
#include <ctime>

#define LIGHT_PURPLE "\033[01;35m"
#define RED "\033[22;31m"
#define RESET "\033[0m"
#define LIGHT_GREEN "\033[01;32m"
using namespace std;

static int positionMax, positionMin;
int GameLevel;
const int MAX_BOARD_SIZE = 10;
Chesspiece player_piece('X');
Chesspiece robot_piece('O');

Game::Game()
{
    gameContinue = true;
}

// getPositionMax
// Purpose:     get the value of positionMax
// Arguments:   None
// Returns:     positionMax (int)
int Game::getPositionMax()
{
    return positionMax;
}

// getPositionMin
// Purpose:     get the value of positionMin
// Arguments:   None
// Returns:     positionMin (int)
int Game::getPositionMin()
{
    return positionMin;
}

// randomMove
// Purpose:     Get the random move of computer
// Arguments:   None
// Returns:     randomly generated position(1-9) (int)
int Game::randomMove()
{
    int n = 0;
    
    // Get the number of empty pieces
    for (int i = 1; i < boardSize(); ++i)
    {
        if (isEmpty(i))
        {
            n++;
        }
    }
    
    int * ArrayofEmptyPieces = new int[n];
    int index = 0;
    
    // Store the position of empty pieces in the array
    for (int i = 1; i < boardSize(); ++i)
    {
        if (isEmpty(i))
        {
            ArrayofEmptyPieces[index] = i;
            index++;
        }
    }
    
    // Get the random generated position
    srand(time(NULL));
    int positionofArray = rand() % n;
    int position = ArrayofEmptyPieces[positionofArray];
    delete [] ArrayofEmptyPieces;
    
    return position;
}

// minimax
// Purpose:     Get the optimal move of computer using Minimax algorithm
// Arguments:   bool playerTurn, int n
// Returns:     max when it is player's turn;  min when it is computer's turn
int Game::minimax(bool playerTurn, int n)
{
    int gain = 0;
    int max = numeric_limits<int>::lowest();
    int min = numeric_limits<int>::max();
    
    GameDecision whoWins = checkForWinner();
    if (whoWins == player || whoWins == computer || isGameADraw())
        return whoWins;
    
    for (int i = 1; i < boardSize(); i++)
    {
        if(isEmpty(i))
        {
            char pieceLabel = playerTurn ? 'X' : 'O'; //place 'X' if it is player's turn, else 'O'
            Chesspiece piece(pieceLabel);
            insertToBoard(i, piece);
            
            gain = minimax(!playerTurn, n + 1);
            
            piece.setPieceLabel('-');
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
            }
            else
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

// isGameADraw
// Purpose:     Check if the game is a draw
// Arguments:   None
// Returns:     If the game is a draw or not (bool)
bool Game::isGameADraw()
{
    GameDecision winResults = checkForWinner();
    bool boardFilled = true;
    
    for (int i = 1; i < boardSize(); i++)
    {
        if (isEmpty(i))
        {
            boardFilled = false;
            break;
        }
    }
    return (winResults == allelse && boardFilled);
}

// checkForConnectingLines
// Purpose:     Check if any player's chesses connect a line (vertical line, horizontal line or diagonal line
// Arguments:   chess (Chesspiece)
// Returns:     If any player's chesses connect a line or not (bool)
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

// checkForWinner
// Purpose:     Check who is the winner
// Arguments:   None
// Returns:     the winner (player or computer)
GameDecision Game::checkForWinner()
{
    GameDecision winResults = allelse;
    
    if (checkForConnectingLines(player_piece))
    {
        winResults = player;
    }
    else if(checkForConnectingLines(robot_piece))
    {
        winResults = computer;
    }
    return winResults;
}

// printManual
// Purpose:     Print the manual to instruct player to input properly
//              First ask if player want to continue the last saved game
//              If so, read the last saved game
//              Otherwize, ask player to choose the level
// Arguments:   None
// Returns:     None
void Game::printManual()
{
    cout << "*****Tic-Tac-Toe*****" << endl;
    cout << "Please familiarize yourself with the layout of the board:\n" << endl;
    cout << "\t\t\t";
    cout << LIGHT_PURPLE;
    for (int i = 1; i < boardSize(); i++)
    {
        cout << i << " ";
        if (i % 3 == 0)
            cout << "\n\t\t\t";
    }
    cout << RESET << endl;
    cout << "Enter \"CONT\" to continue playing the last saved game, enter \"NEW\" to start a new game \n";
    string cmd;
    cin >> cmd;
    bool validInput = 0;
    
    while (!validInput)
    {
        if (cmd == "CONT")
        {
            validInput = 1;
            readGame();
        }
        else if (cmd == "NEW")
        {
            validInput = 1;
            cout << LIGHT_PURPLE << "\nChoose the level of your opponent. Enter 1 or 2." << RESET << endl;
            cout << "\t1. Easy \t 2. Impossible" << endl;
            cin >> GameLevel;
            while (GameLevel != 1 && GameLevel != 2)
            {
                cout << "Please choose a level" << endl;
                cout << "\t1. Easy \t 2. Impossible" << endl;
                cin >> GameLevel;
            }
            cout << LIGHT_PURPLE << "\nEnter 1 - 9 from your keyboard to place your move."<< RESET <<endl;
            cout << "The board is empty now." << endl;
            print_board();
        }
        else
        {
            cout << "Please enter a valid input \n";
            cout << "Enter \"CONT\" to continue playing the last saved game, enter \"NEW\" to start a new game \n";
            cin >> cmd;
        }
    }
}

// start
// Purpose:     Start the game and continue the game round by round until the game ends or the
//              player wants to save the game and exit
// Arguments:   None
// Returns:     None
void Game::start()
{
    cout << "You will start first! You will be \"X\":" << endl;
    gameContinue = true;
    string input;
    
    // loop until there is a winner or user saves the current game
    while(gameContinue)
    {
        cout << "It's your turn now, ";
        cout << "enter " << LIGHT_PURPLE << "\"SAVE\"" << RESET << " to save the current game and exit.\n";
        cout << "Enter 1-9 to place your move: "<<endl;
        
        // Get user input
        cin >> input;
        int movePosition = atoi(input.c_str());
        
        // Save current game if user requests it
        if (input == "SAVE")
        {
            saveGame();
            gameContinue = false;
            continue;
        }
        
        // Check if user input is valid
        // If so, check if the position is empty
        while  (!isValidPos(movePosition) || !isEmpty(movePosition))
        {
            cout << RED << "Please choose a valid move!" << RESET << endl;
            cin >> input;
            movePosition = atoi(input.c_str());
        }
        insertToBoard(movePosition, player_piece);
        
        cout << "Board:\n";
        print_board();
        
        GameDecision winner = checkForWinner();
        
        if (winner == player)
        {
            cout << LIGHT_PURPLE << "You win!:)\n" << RESET << endl;
            gameContinue = false;
        }
        else if (isGameADraw())
        {
            cout << LIGHT_PURPLE << "It is a draw guys!" << RESET << endl;
            gameContinue = false;
        }
        else
        {   // Easy level robot makes random move
            if (GameLevel == 1)
            {
                int position = randomMove();
                insertToBoard(position, robot_piece);
                
                cout << "Robot is making a move..." << endl;
                cout << "And robot puts a O at " << position << endl;
                print_board();
            }
            
            // Impossible level robot makes move
            if (GameLevel == 2)
            {
                minimax(false, 0); //false indicates it is computer's turn
                insertToBoard(getPositionMin(), robot_piece);
                
                cout << "Robot is making a move..." << endl;
                cout << "And robot puts a O at " << getPositionMin() << endl;
                print_board();
            }
                
            if (winner == computer)
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
        myfile << GameLevel;
        myfile.close();
    }
    else cout << "Unable to save the game";
}

// readGame
// Purpose:     Reload the last saved game
// Arguments:   None
// Returns:     None
void Game::readGame(){
    char piece;
    ifstream myfile ("board.txt");
    if (myfile.is_open())
    {
        int position = 1;
        while (myfile >> piece)
        {
            if (piece == 'X')
            {
                insertToBoard(position, player_piece);
            }
            else if (piece == 'O')
            {
                insertToBoard(position, robot_piece);
            }
            // Use ASCII Chart to get the integer value of GameLevel
            else if (isdigit(piece))
            {
                GameLevel = piece - '0';
            }
            position ++;
        }
        
        cout << "\nBoard loaded from the last saved game:\n";
        print_board();
        myfile.close();
    }
    
    else
    {
        cout << "Unable to open file." << endl;
        cout << "Start a new game." << endl;
        cout << LIGHT_PURPLE << "\nChoose the level of your opponent. Enter 1 or 2." << RESET << endl;
        cout << "\t1. Easy \t 2. Impossible" << endl;
        cin >> GameLevel;
        while (GameLevel != 1 && GameLevel != 2)
        {
            cout << "Please choose a level" << endl;
            cout << "\t1. Easy \t 2. Impossible" << endl;
            cin >> GameLevel;
        }
        cout << "The board is empty now." << endl;
        print_board();
    }
}
