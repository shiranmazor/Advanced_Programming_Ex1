#include "BattleBoard.h"

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

