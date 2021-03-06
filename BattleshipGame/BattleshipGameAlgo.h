#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "IBattleshipGameAlgo.h"
#include "BattleBoard.h"
using namespace std;

#define MyHitMark '*'
#define OpHitMark '#'
#define MyMissMark '~'
#define OpMissMark '^'
#define MySinkMark '!'
#define OpSinkMark '?'

class BattleshipGameAlgo :IBattleshipGameAlgo
{
public:
	Player playerName;
	BattleBoard* playerBoard = nullptr;
	string attackFilePath;
	ifstream attackFile;

	// Blocking Copy and Assignment
	BattleshipGameAlgo(const BattleshipGameAlgo&) = delete;
	BattleshipGameAlgo& operator = (const BattleshipGameAlgo&) = delete;

	//constructor
	BattleshipGameAlgo(Player playerName, string attackFilePath)
	{
		this->playerName = playerName;
		this->attackFilePath = attackFilePath;
		//load attack file to file handle assuming file path is correct:
		this->attackFile.open(attackFilePath);
		if (this->attackFile.fail())
		{
			//error message for file not found
			this->attackFile.close();

		}

	}
	~BattleshipGameAlgo()
	{
		if (playerBoard != nullptr)
			delete playerBoard;
		//close handle to attack file
		this->attackFile.close();
	}

	virtual void setBoard(const char** board, int numRows, int numCols) override;
	virtual std::pair<int, int> attack() override;
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override;
	/*
	*check if attack line is valid and contain indexes in range, one comma and doesn't contain
	*white spacecs at the begining or end else return False
	*
	*/
	bool isAttackLineValid(string line);
};