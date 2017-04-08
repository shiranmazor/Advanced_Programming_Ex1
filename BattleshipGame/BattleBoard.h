#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include "Common.h"
#include "IBattleshipGameAlgo.h"
#include <string.h>
#include <iostream>
using namespace std;

#define isPlayerChar(x, y) (x==A && (isupper(y) || isspace(y)) || (x==B && (islower(y) || isspace(y))))
#define isOppChar(x, y) ((x==A && islower(y)) || (x==B && isupper(y)))
#define HitMarkA '*'
#define HitMarkB '#'

const char idx2ship[8] = { 'b', 'p', 'm', 'd', 'B', 'P', 'M', 'D' };
const std::unordered_map<char, int> ship2idx = {
	{ 'b', 0 },{ 'p', 1 },{ 'm', 2 },{ 'd', 3 },{ 'B', 4 },{ 'P', 5 },{ 'M', 6 },{ 'D', 7 },
};

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

		// convert invalid chars to spaces
		for (int i = 0; i < this->R; i++)
			for (int j = 0; j < this->C; j++)
				if (!isCharValid(this->board[i][j])) this->board[i][j] = ' ';

		if (!this->isBoardValid())
		{
			// handle invalid board
			cout << "board not valid" << endl;
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
	void getPlayerBoard(Player player, char** &pBoard);
	AttackResult performGameMove(Player p, pair<int, int> move);
};
