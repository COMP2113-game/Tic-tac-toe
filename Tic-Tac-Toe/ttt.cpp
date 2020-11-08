#include <iostream>
#include <string>

using namespace std;

const int ROWsnum = 3;
const int COLsnum = 3;
int row;
int col;
int winner = 0;
bool gameover = false;
char board[COLsnum][ROWsnum] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
string playername1;
string playername2;

void printboard()
{
	cout << board[0][2] << " | " << board[1][2] << " | " << board[2][2] << endl;
	cout << "__________" << endl;
	cout << board[0][1] << " | " << board[1][1] << " | " << board[2][1] << endl;
	cout << "__________" << endl;
	cout << board[0][0] << " | " << board[1][0] << " | " << board[2][0] << endl;
}

void movex()
{
	cout << "Column:";
	cin >> col;
	cout << endl << "Row:";
	cin >> row;
	board[col][row] = 'X';
}

void moveo()
{
	cout << "Column:";
	cin >> col;
	cout << endl << "Row:";
	cin >> row;
	board[col][row] = 'O';
}

void checkwinner()
{
	if (gameover == false)
	{
		winner = -1;
	}
	else if (board[0][2] == board[1][2] == board[2][2])
	{
		if(board[0][2] == 'X')
		{
			winner = 1;
		}
		else
		{
			winner = 2;
		}
	}
	else if (board[0][1] == board[1][1] == board[2][1])
	{
		if(board[0][1] == 'X')
		{
			winner = 1;
		}
		else
		{
			winner = 2;
		}
	}
	else if (board[0][0] == board[1][0] == board[2][0])
	{
		if(board[0][0] == 'X')
		{
			winner = 1;
		}
		else
		{
			winner = 2;
		}
	}
	else if (board[0][0] == board[0][1] == board[0][2])
	{
		if(board[0][0] == 'X')
		{
			winner = 1;
		}
		else
		{
			winner = 2;
		}
	}
	else if (board[1][0] == board[1][1] == board[1][2])
	{
		if(board[1][0] == 'X')
		{
			winner = 1;
		}
		else
		{
			winner = 2;
		}
	}
	else if (board[2][0] == board[2][1] == board[2][2])
	{
		if(board[2][0] == 'X')
		{
			winner = 1;
		}
		else
		{
			winner = 2;
		}
	}
	else if (board[0][2] == board[1][1] == board[2][0])
	{
		if(board[0][2] == 'X')
		{
			winner = 1;
		}
		else
		{
			winner = 2;
		}
	}
	else if (board[0][0] == board[1][1] == board[2][2])
	{
		if(board[0][0] == 'X')
		{
			winner = 1;
		}
		else
		{
			winner = 2;
		}
	}
	else if (gameover == true)
	{
		winner = 5;
	}
	system("PAUSE");
}

void checkgameover()
{
	int otherc = 5;
	for(int c = 0; c <= 2; c++)
	{
		for(int r = 0; r <= 2; r++)
		{
			if(board[c][r] == ' ')
			{
				gameover = false;
				c = 5;
				r = 5;
				otherc = 10;
			}
		}
	}
	if(otherc == 5)
	{
		gameover == true;
	}
	else if(otherc == 10)
	{

	}
}

int main()
{
	cout << "Welcome to the game!" << endl << endl;
	cout << "Player 1, enter your name:";
	cin >> playername1;
	cout << "Hello " << playername1 << ", you are X." << endl;
	cout << "Player 2, enter your name:";
	cin >> playername2;
	cout << "Hello " << playername2 << ", you are O." << endl;
	system("PAUSE>nul");
	cout << "So " << playername1 << ", its you're turn." << endl;
	cout << "To move, enter the column you would like to choose and press return." << endl << "Then enter the row you would like to choose and press return." << endl;
	cout << "The bottom left is Col:0 and Row:0, the middle is Col:1 and Row:1, and the top right is Col:2 and Row:2" << endl;
	printboard();
	movex();
	printboard();
	cout << endl << "Now its " << playername2 << "'s turn." << endl;
	moveo();
	printboard();
	for(int i = winner; i <= 1; i++)
	{
		cout << endl << "X turn" << endl;
		movex();
		printboard();
		cout << endl << "O turn" << endl;
		moveo();
		printboard();
		checkgameover();
		checkwinner();
		if(winner == 5)
		{
			cout << "Stale mate. Nobody wins.";
			system("PAUSE>nul");
		}
		else if (winner == 1)
		{
			cout << "Congrats " << playername1 << "! X wins!" << endl;
			system("PAUSE>nul");
		}
		else if (winner == 2)
		{
		cout << "Congrats " << playername2 << "! O wins!" << endl;
		system("PAUSE>nul");
	}
}
	return 0;
}
