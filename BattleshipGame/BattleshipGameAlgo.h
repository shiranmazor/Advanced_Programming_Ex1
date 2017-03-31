#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include "IBattleshipGameAlgo.h"
using namespace std;
enum Player { A,B };

class BattleshipGameAlgo:IBattleshipGameAlgo
{
public:
	Player playerName;
	int R;
	int C;
	char** board = nullptr;
	string attackFilePath;
	ifstream attackFile;

	//constructor
	BattleshipGameAlgo( Player playerName, string attackFilePath): R(10), C(10),board(NULL)
	{
		this->playerName = playerName;
		this->attackFilePath = attackFilePath;
		//load attack file to file handle assuming file path is correct:
		attackFile.open(attackFilePath);
		if (attackFile.fail())
		{
			//error message for file not found
			attackFile.close();
			
		}

	}
	~BattleshipGameAlgo()
	{
		if (board != NULL)
		{
			delete[] board;
		}
	}

	virtual void setBoard(const char** board, int numRows, int numCols) override;
	virtual std::pair<int, int> attack() override;
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override;
};