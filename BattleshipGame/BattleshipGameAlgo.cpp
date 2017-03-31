#include "BattleshipGameAlgo.h"
#include <cctype>
#define isPlayerTool(x, y) (x==A && (isupper(y) && !isspace(y)) || (x==B && (islower(y) && !isspace(y))))

void BattleshipGameAlgo::setBoard(const char** board, int numRows, int numCols)
{
	
	this->playerBoard = new BattleBoard(board, numRows, numCols);

	//init board tools member:
	for (int i = 0; i < this->playerBoard->R; i++)
	{
		for (int j = 0; j < this->playerBoard->C; j++)
		{
			if(isPlayerTool(this->playerName, this->playerBoard->board[i][j]))
			{
				pair<char, int> p;
				if (std::tolower(this->playerBoard->board[i][j]) == 'b')
					p = pair<char, int>('b', 1);
				else if (std::tolower(this->playerBoard->board[i][j]) == 'p')
					p = pair<char, int>('p', 2);
				else if (std::tolower(this->playerBoard->board[i][j]) == 'm')
					p = pair<char, int>('m', 3);
				else if (std::tolower(this->playerBoard->board[i][j]) == 'd')
					p = pair<char, int>('d', 4);

				this->boardTools.push_back(p);
			}
			
		}
	}
}
std::pair<int, int> BattleshipGameAlgo::attack()
{
	return std::pair<int, int>(0, 0);
}
void BattleshipGameAlgo::notifyOnAttackResult(int player, int row, int col, AttackResult result)
{
	
}



