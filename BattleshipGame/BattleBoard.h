#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class BattleBoard
{
public:
	string boardName;
	string playerName;
	int R;
	int C;
	char** matrix;

	BattleBoard() : matrix(NULL) ,R(10),C(10){}
	~BattleBoard()
	{
		if (matrix != NULL)
		{
			delete[] matrix;
		}
	}
};