#include "BattleBoard.h"
#include <set>
#include <iostream>

/*
0 - no direction (ship size 1 or adjecent ships error)
1 - going right
2 - going down */
int _getShipDirection(BattleBoard* b, int i, int j)
{
	if (j != b->C - 1)
		if (b->board[i][j + 1] == b->board[i][j])
			return 1;
	if (i != b->R - 1)
		if (b->board[i + 1][j] == b->board[i][j])
			return 2;
	
	return 0;
}


bool BattleBoard::isBoardValid()
{
	int countA = 0;
	int countB = 0;
	std::set<pair<int, int>> checkedBoxes;
	pair<int, int> box;
	char currentShip;
	int dir;
	bool badShape[8] = { false };
	bool tooClose = false;
	bool allGood = false;

	cout << "is valid called" << endl;
	for (int i = 0; i < this->R; i++)
	{
		for (int j = 0; j < this->C; j++)
		{
			box = std::make_pair(i, j);
			
			// ignore empty, invalid or already checked boxes (in case of full ship scan)
			if (this->board[i][j] == ' ' || checkedBoxes.find(box) != checkedBoxes.end()) continue;
			
			checkedBoxes.insert(box);
			allGood = false;
			dir = _getShipDirection(this, i, j);

			for (int l = 0; l <= getShipSize(this->board[i][j]); l++){
				if (dir == 1)
				{
					if (l == getShipSize(this->board[i][j]))
					{
						if (j + l < this->C && this->board[i][j + l] == this->board[i][j]) badShape[ship2idx.at(this->board[i][j])] = true;
						else allGood = true;
					}
					else if (j + l == this->C || this->board[i][j + l] != this->board[i][j]) badShape[ship2idx.at(this->board[i][j])] = true;
					else {
						checkedBoxes.insert(std::make_pair(i, j + l));
						allGood = true;
					}

					if (this->board[i - 1][j + l] != ' ' || this->board[i - 1][j + l - 1] != ' ') tooClose = true;
				}
				if (dir == 2)
				{
					if (l == getShipSize(this->board[i][j]))
					{
						if (i + l < this->R && this->board[i + l][j] == this->board[i][j]) badShape[ship2idx.at(this->board[i][j])] = true;
						else allGood = true;
						if (i + l < this->R && (this->board[i + l][j] != ' ' || this->board[i + l][j - 1] != ' ' || this->board[i + l][j + 1] != ' ')) tooClose = true;
					}
					else if (i + l == this->R || this->board[i + l][j] != this->board[i][j]) badShape[ship2idx.at(this->board[i][j])] = true;
					else
					{
						checkedBoxes.insert(std::make_pair(i + l, j));
						allGood = true;
						if (this->board[i + l][j - 1] != ' ' || this->board[i + l][j + 1] != ' ') tooClose = true;
					}
			 
				}
				if (dir == 0)
				{
					if (getShipSize(this->board[i][j]) != 1) badShape[ship2idx.at(this->board[i][j])] = true;
					else allGood = true;

					if (i < this->R - 1 && this->board[i + 1][j] != ' ') tooClose = true;
					if (j < this->C - 1 && this->board[i][j + 1] != ' ') tooClose = true;
					if (i < this->R - 1 && j < this->C - 1 && this->board[i + 1][j + 1] != ' ') tooClose = true;
				}
			}
			
			if (allGood)
			{
				if (isPlayerChar(A, this->board[i][j])) countA++;
				else countB++;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (badShape[i]) cout << "Wrong size or shape for ship " << idx2ship[i] << " for player A" << endl;
		if (badShape[i + 4]) cout << "Wrong size or shape for ship " << idx2ship[i + 4] << " for player B" << endl;
	}
	//cout << "countA " << countA << endl;
	//cout << "countB " << countB << endl;
	if (countA > 5) cout << "Too many ships for player A" << endl;
	if (countA < 5) cout << "Too few ships for player A" << endl;
	if (countB > 5) cout << "Too many ships for player B" << endl;
	if (countB < 5) cout << "Too few ships for player B" << endl;

	if (tooClose) cout << "Adjacent Ships on Board" << endl;
	
	return true;
}

int BattleBoard::CalcScore()
{
	return 0;
}

Player BattleBoard::CheckVictory()
{
	Player winner = A;
	return winner;
}

void BattleBoard::getPlayerBoard(Player player, char** &pBoard)
{
	pBoard = new char*[this->R];
	for (int i = 0; i < this->C; i++)
		pBoard[i] = new char[this->C];

	for (int i = 0; i < this->R; i++)
	{
		for (int j = 0; j < this->C; j++)
		{
			if (isPlayerChar(player, this->board[i][j]))
				pBoard[i][j] = this->board[i][j];
			else 
				pBoard[i][j] = ' ';
		}
	}
}

AttackResult BattleBoard::performGameMove(Player p, pair<int, int> move)
{	
	char c = this->board[move[0]][move[1]];
	if (!isspace(c) && isOppChar(p, c)){
		this->board[move[0]][move[1]] = p == A ? HitMarkA : HitMarkB;
		//TODO: add check for sink
		return AttackResult::Hit;
	}
	else{
		return AttackResult::Miss;
	}
}

