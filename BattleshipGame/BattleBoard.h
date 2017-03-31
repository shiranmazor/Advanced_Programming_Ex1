#pragma once
#include <string>
#include <fstream>
#include "Common.h"
using namespace std;

class BattleBoard
{
public:
	int R;
	int C;
	//bool is_main_board;
	string* board;

	//constructor
	BattleBoard(string boardFilePath):R(10), C(10)
	{	
		ifstream boardFile(boardFilePath);
		this->board = new string[R];

		if (boardFile.fail())
		{
			//error message for file not found
			boardFile.close();
		}

		for (int i = 0; i < R; i++)
		{
			std::getline(boardFile, this->board[i]);
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

	BattleBoard(string* initBoard) :R(10), C(10)
	{
		this->board = initBoard;
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
	string CheckVictory();
	string* getPlayerBoard(Player player);
};
