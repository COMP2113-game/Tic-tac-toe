#include "Game.h"
#include "Chesspiece.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <vector>

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
int n_player = 0;
int n_robot = 0;

int * playermovements = new int [5];
int * robotmovements = new int [5];

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
    if (whoWins == player || whoWins == robot || isGameADraw())
        return whoWins;
    
    for (int i = 1; i < boardSize(); i++)
    {
        if(isEmpty(i))
        {
            char pieceLabel = playerTurn ? 'X' : 'O'; //place 'X' if it is player's turn, else 'O'
            Chesspiece piece(pieceLabel);
            insertToBoard(i, piece);
            // insert into movement array
            if (pieceLabel == 'X') {
                playermovements[n_player] = i;
                n_player ++;
            }
            else {
                robotmovements[n_robot] = i;
                n_robot ++;
            }
            gain = minimax(!playerTurn, n + 1);
            
            piece.setPieceLabel('-');
            insertToBoard(i, piece);
            // delete from movement array
            if (pieceLabel == 'X') {
                n_player --;
                playermovements[n_player] = 0;
            }
            else {
                n_robot --;
                robotmovements[n_robot] = 0;
            }

            if (playerTurn)
            {
                if (gain > max)
                {
                    max = gain;
                    if (n == 0) positionMax = i;
                }
            }
            else
            {
                if (gain < min)
                {
                    min = gain;
                    if (n == 0) positionMin = i;
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

// isSubset
// Purpose:     Check if arr2 is cintained in arr1
// Arguments:   arr1[] (int), arr2[] (int), n_arr1 (int), n_arr2 (int)
// Returns:     If the array is the subset of the case or not (bool)
bool Game::isSubset(int arr1[], int arr2[], int arr1Size, int arr2Size)
{
    int i = 0; 
    int j = 0; 
    for (i = 0; i < arr2Size; i++) { 
        for (j = 0; j < arr1Size; j++) { 
            if (arr2[i] == arr1[j]) 
                break; 
        } 
  
        //If break isn't executed, arr2 is not the subset of arr1
        if (j == arr1Size) 
            return 0; 
    } 
  
    //It the function is executed to here, all elements of arr2[] are present in arr1[]
    return 1; 
}


// checkForConnectingLines
// Purpose:     Check if any player's chesses connect a line (vertical line, horizontal line or diagonal line
// Arguments:   chess (Chesspiece)
// Returns:     If any player's chesses connect a line or not (bool)
bool Game::checkForConnectingLines(int * movements)
{
    
    int case1[3] = {1,2,3};
    int case2[3] = {4,5,6};
    int case3[3] = {7,8,9};
    int case4[3] = {1,4,7};
    int case5[3] = {2,5,8};
    int case6[3] = {3,6,9};
    int case7[3] = {1,5,9};
    int case8[3] = {3,5,7};
    
    return (
        isSubset(movements, case1, sizeof(movements),3)||
        isSubset(movements, case2, sizeof(movements),3)||
        isSubset(movements, case3, sizeof(movements),3)||
        isSubset(movements, case4, sizeof(movements),3)||
        isSubset(movements, case5, sizeof(movements),3)||
        isSubset(movements, case6, sizeof(movements),3)||
        isSubset(movements, case7, sizeof(movements),3)||
        isSubset(movements, case8, sizeof(movements),3));
}

// checkForWinner
// Purpose:     Check who is the winner
// Arguments:   None
// Returns:     the winner (player or computer)
GameDecision Game::checkForWinner()
{
    GameDecision winResults = allelse;
    
    if (checkForConnectingLines(playermovements))
    {
        winResults = player;
    }
    else if(checkForConnectingLines(robotmovements))
    {
        winResults = robot;
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
        playermovements[n_player] = movePosition;
        n_player ++;
        
        cout << "Board:\n";
        print_board();
        
        GameDecision winner = checkForWinner();
        
        if (winner == player)
        {
            cout << LIGHT_PURPLE << "You win!:)\n" << RESET << endl;
            delete [] playermovements;
            delete [] robotmovements;
            gameContinue = false;
        }
        else if (isGameADraw())
        {
            cout << LIGHT_PURPLE << "It is a draw guys!" << RESET << endl;
            delete [] playermovements;
            delete [] robotmovements;
            gameContinue = false;
        }
        else
        {   // Easy level robot makes random move
            if (GameLevel == 1)
            {
                int position = randomMove();
                insertToBoard(position, robot_piece);
                robotmovements[n_robot] = position;
                n_robot ++;

                cout << "Robot is making a move..." << endl;
                cout << "And robot puts a O at " << position << endl;
                
                print_board();
            }
            
            // Impossible level robot makes move
            if (GameLevel == 2)
            {
                minimax(false, 0); //false indicates it is computer's turn
                insertToBoard(getPositionMin(), robot_piece);
                robotmovements[n_robot] = getPositionMin();
                n_robot ++;
                
                cout << "Robot is making a move..." << endl;
                cout << "And robot puts a O at " << getPositionMin() << endl;
                
                print_board();
            }
            
            winner = checkForWinner();
            
            if (winner == robot)
            {
                cout << LIGHT_PURPLE << "Robot wins!" << RESET << endl;
                delete [] playermovements;
                delete [] robotmovements;
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
                playermovements[n_player] = position;
                n_player ++;

            }
            else if (piece == 'O')
            {
                insertToBoard(position, robot_piece);
                robotmovements[n_robot] = position;
                n_robot ++;
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
