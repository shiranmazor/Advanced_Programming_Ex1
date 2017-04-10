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
	//Todo: create ships map
	int countA = 0;
	int countB = 0;
	std::set<pair<int, int>> checkedBoxes;
	pair<int, int> box;
	int dir, totalShape = 0;
	bool badShape[8] = { false };
	bool tooClose = false;
	bool sizeGood;

	for (int i = 0; i < this->R; i++)
	{
		for (int j = 0; j < this->C; j++)
		{
			box = std::make_pair(i, j);

			// ignore empty, invalid or already checked boxes (in case of full ship scan)
			if (this->board[i][j] == ' ' || checkedBoxes.find(box) != checkedBoxes.end()) continue;

			checkedBoxes.insert(box);
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
					else checkedBoxes.insert(std::make_pair(i, j + l));

					if (i < this->R - 1 && (this->board[i + 1][j + l] != ' ' || this->board[i + 1][j + l - 1] != ' ')) tooClose = true;
				}
				else if (dir == 2)
				{
					if (l == getShipSize(this->board[i][j]))
					{
						if (i + l < this->R && this->board[i + l][j] == this->board[i][j]) badShape[ship2idx.at(this->board[i][j])] = true;
						else sizeGood = true;
						if (i + l < this->R && (this->board[i + l][j] != ' ' || (j > 0 && this->board[i + l][j - 1] != ' ') || (j < this->C - 1 && this->board[i + l][j + 1] != ' '))) tooClose = true;
					}
					else if (i + l == this->R || this->board[i + l][j] != this->board[i][j]) badShape[ship2idx.at(this->board[i][j])] = true;
					else
					{
						checkedBoxes.insert(std::make_pair(i + l, j));
						if ((j > 0 && this->board[i + l][j - 1] != ' ') || this->board[i + l][j + 1] != ' ') tooClose = true;
					}

				}
				else // dir == 0
				{
					if (getShipSize(this->board[i][j]) != 1) badShape[ship2idx.at(this->board[i][j])] = true;
					else sizeGood = true;

					if (i < this->R - 1 && this->board[i + 1][j] != ' ') tooClose = true;
					if (j < this->C - 1 && this->board[i][j + 1] != ' ') tooClose = true;
					if (i < this->R - 1 && j < this->C - 1 && this->board[i + 1][j + 1] != ' ') tooClose = true;
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

	if (countA > 5) cout << "Too many ships for player A" << endl;
	if (countA < 5) cout << "Too few ships for player A" << endl;
	if (countB > 5) cout << "Too many ships for player B" << endl;
	if (countB < 5) cout << "Too few ships for player B" << endl;

	if (tooClose) cout << "Adjacent Ships on Board" << endl;


	return (countA == 5 && countB == 5 && !tooClose && totalShape == 0);
}

pair<int, int> BattleBoard::CalcScore()
{
	return  pair<int, int>(0,0);
}
int BattleBoard::CheckVictory()
{
	Player winner = A;
	return -1;
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
	char c = this->board[std::get<0>(move)][std::get<1>(move)];
	if (!isspace(c) && isOppChar(p, c)) {
		this->board[std::get<0>(move)][std::get<1>(move)] = p == A ? HitMarkA : HitMarkB;
		//TODO: add check for sink
		return AttackResult::Hit;
	}
	else {
		return AttackResult::Miss;
	}
}

 bool BattleBoard::isSelfHit(Player currentPlayer, pair<int, int> attackMove)
{
	if ((currentPlayer == A && this->board[attackMove.first][attackMove.second] == HitMarkA)||
		(currentPlayer == B && this->board[attackMove.first][attackMove.second] == HitMarkB))
	{
		//player  attack himself
		return true;
	}
	return false;
}

