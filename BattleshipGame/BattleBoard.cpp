#include "BattleBoard.h"

#define isPlayerChar(x, y) (x==A && (isupper(y) || isspace(y)) || (x==B && (islower(y) || isspace(y))))

bool BattleBoard::isBoardValid()
{
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

char** BattleBoard::getPlayerBoard(Player player)
{
	char** res = new char*[this->R];
	for (int i = 0; i < this->C; i++) this->board[i] = new char[this->C];

	for (int i = 0; i < this->R; i++)
	{
		for (int j = 0; j < this->C; j++)
		{
			if (isPlayerChar(player, this->board[i][j])) res[i][j] = this->board[i][j];
			else res[i][j] = ' ';
		}
	}
	return res;
}
