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
	int dir, totalShape = 0;
	bool badShape[8] = { false };
	bool tooClose = false;
	bool sizeGood;
	Vessel* currShip;

	for (int i = 0; i < this->R; i++)
	{
		for (int j = 0; j < this->C; j++)
		{
			box = std::make_pair(i, j);

			// ignore empty, invalid or already checked boxes (in case of full ship scan)
			if (this->board[i][j] == ' ' || checkedBoxes.find(box) != checkedBoxes.end()) continue;

			checkedBoxes.insert(box);
			currShip = new Vessel(this->board[i][j]);
			this->ships[makeKey(box)] = currShip;
			sizeGood = false;
			dir = _getShipDirection(this, i, j);

			for (int l = 0; l <= getShipSize(this->board[i][j]); l++) {
				if (dir == 1)
				{
					if (l == getShipSize(this->board[i][j]))
					{
						if (j + l < this->C && this->board[i][j + l] == this->board[i][j]) badShape[ship2idx.at(this->board[i][j])] = true;
						else sizeGood = true;
					}
					else if (j + l == this->C || this->board[i][j + l] != this->board[i][j]) badShape[ship2idx.at(this->board[i][j])] = true;
					else {
						box = std::make_pair(i, j + l);
						checkedBoxes.insert(box);
						this->ships[makeKey(box)] = currShip;
					}

					if (i < this->R - 1 && this->board[i + 1][j + l] != ' ') tooClose = true;
				}
				else if (dir == 2)
				{
					if (l == getShipSize(this->board[i][j]))
					{
						if (i + l < this->R && this->board[i + l][j] == this->board[i][j]) badShape[ship2idx.at(this->board[i][j])] = true;
						else sizeGood = true;
						if (i + l < this->R && this->board[i + l][j] != ' ') tooClose = true;
					}
					else if (i + l == this->R || this->board[i + l][j] != this->board[i][j]) badShape[ship2idx.at(this->board[i][j])] = true;
					else
					{
						box = std::make_pair(i + l, j);
						checkedBoxes.insert(box);
						this->ships[makeKey(box)] = currShip;
						if ((j > 0 && this->board[i + l][j - 1] != ' ') || this->board[i + l][j + 1] != ' ') tooClose = true;
					}

				}
				else // dir == 0
				{
					if (getShipSize(this->board[i][j]) != 1) badShape[ship2idx.at(this->board[i][j])] = true;
					else sizeGood = true;

					if (i < this->R - 1 && this->board[i + 1][j] != ' ') tooClose = true;
					if (j < this->C - 1 && this->board[i][j + 1] != ' ') tooClose = true;
				}
			}

			if (sizeGood)
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
		totalShape += badShape[i] + badShape[i + 4];
	}

	if (countA > this->playerToolsNum) cout << "Too many ships for player A" << endl;
	if (countA < this->playerToolsNum) cout << "Too few ships for player A" << endl;
	if (countB > this->playerToolsNum) cout << "Too many ships for player B" << endl;
	if (countB < this->playerToolsNum) cout << "Too few ships for player B" << endl;

	if (tooClose) cout << "Adjacent Ships on Board" << endl;


	return (countA == this->playerToolsNum && countB == this->playerToolsNum && !tooClose && totalShape == 0);
}

pair<int, int> BattleBoard::CalcScore()
{
	pair<int, int> scores = std::make_pair(0, 0);
	std::set<Vessel*> seenVessels;

	for (auto const& element : this->ships)
	{
		if (element.second->size == element.second->hitNum && seenVessels.find(element.second) == seenVessels.end())
		{
			//ship has sinked!
			seenVessels.insert(element.second);
			if (element.second->player == B) 
				scores.first += getShipScore(element.second->type);
			else 
				scores.second += getShipScore(element.second->type);
		}
	}
	return scores;
}

int BattleBoard::CheckVictory()
{
	int winner = -1;
	int countA = 0, countB = 0;
	std::set<Vessel*> seenVessels;

	for (auto const& element : this->ships)
	{
		if (element.second->size == element.second->hitNum && seenVessels.find(element.second) == seenVessels.end())
		{
			seenVessels.insert(element.second);
			if (element.second->player == A) countA++;
			else countB++;
		}
	}
	
	if (countA == this->playerToolsNum) winner = B;
	else if (countB == this->playerToolsNum) winner = A;

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
	char c = this->board[move.first][move.second];
	if (!isspace(c)) {
		if (isAlreadyHit(c)) { 
			return (this->ships[makeKey(move)]->hitNum == this->ships[makeKey(move)]->size) ? AttackResult::Miss : AttackResult::Hit;
		}
		if (isupper(c) || islower(c)) {
			this->board[move.first][move.second] = isupper(c) ? HitMarkA : HitMarkB;
			this->ships[makeKey(move)]->hitNum++;
			return (this->ships[makeKey(move)]->hitNum == this->ships[makeKey(move)]->size) ? AttackResult::Sink : AttackResult::Hit;
		}
	}
	return AttackResult::Miss;
}
