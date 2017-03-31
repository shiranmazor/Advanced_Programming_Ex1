#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "IBattleshipGameAlgo.h"
#include "BattleBoard.h"
using namespace std;


class BattleshipGameAlgo:IBattleshipGameAlgo
{
public:
	Player playerName;
	BattleBoard* playerBoard ;
	string attackFilePath;
	ifstream attackFile;
	vector<pair<char, int>> boardTools;


	//constructor
	BattleshipGameAlgo(Player playerName, string attackFilePath)
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
		delete playerBoard;
	}

	virtual void setBoard(const char** board, int numRows, int numCols) override;
	virtual std::pair<int, int> attack() override;
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override;
};