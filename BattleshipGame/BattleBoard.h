#pragma once
#include <string>
#include <fstream>
#include "Common.h"
using namespace std;

#define isPlayerChar(x, y) (x==A && (isupper(y) || isspace(y)) || (x==B && (islower(y) || isspace(y))))

class BattleBoard
{
public:
	int R;
	int C;
	//bool is_main_board;
	char** board;

	//constructor
	BattleBoard(string boardFilePath, int R=10, int C=10)
	{	
		ifstream boardFile(boardFilePath);
		string temp;
		this->R = R;
		this->C = C;
		this->board = new char*[this->R];
		for (int i = 0; i < this->C; i++) this->board[i] = new char[this->C];

		if (boardFile.fail())
		{
			//error message for file not found
			boardFile.close();
		}

		for (int i = 0; i < this->R; i++)
		{
			std::getline(boardFile, temp);
			// copy C chars
			if (temp.length() >= this->C)
				temp.copy(this->board[i], this->C);
				
			else {
				temp.copy(this->board[i], temp.length());
				for (int j = temp.length() - 1; j < this->C; j++) this->board[i][j] = ' ';
			}

			if (std::ifstream::eofbit){
				// eof reached in less than R line, print error
			}
		}
		boardFile.close();

		if (!this->isBoardValid())
		{
			// handle invalid board
		}
	}

	BattleBoard(const char** initBoard, int R = 10, int C = 10)
	{
		this->R = R;
		this->C = C;

		//copy the init board to  new board member
		this->board = new char*[this->R];
		for (int i = 0; i < this->C; i++) this->board[i] = new char[this->C];
		
		for (int i = 0; i < this->R; i++)
		{
				this->board[i] = _strdup(initBoard[i]);
		}
		if (!this->isBoardValid())
		{
			// handle invalid board
		}
	}

	// destructor
	~BattleBoard()
	{
		if (this->board != NULL)
		{
			delete[] this->board;
		}
	}

	bool isBoardValid();
	int CalcScore();
	Player CheckVictory();
	char** getPlayerBoard(Player player);
};
