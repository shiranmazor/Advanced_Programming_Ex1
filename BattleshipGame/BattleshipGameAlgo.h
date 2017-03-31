#include <iostream>
#pragma once
#include <string>
#include <fstream>
#include "IBattleshipGameAlgo.h"
using namespace std;

class BattleshipGameAlgo:IBattleshipGameAlgo
{
public:
	virtual void setBoard(const char** board, int numRows, int numCols) override;
	virtual std::pair<int, int> attack() override;
	virtual void notifyOnAttackResult(int player, int row, int col, AttackResult result) override;
};