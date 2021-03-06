#include "BattleshipGameAlgo.h"
#include "Game.h"

void gotoxy(short col, short row)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { col, row };
	SetConsoleCursorPosition(h, c);
}
void setTextColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}


/*
* get current working directory path
*/
BattleshipGameAlgo* swapPlayer(BattleshipGameAlgo* current, BattleshipGameAlgo* pA, BattleshipGameAlgo* pB)
{
	if (current->playerName == pA->playerName)
		return pB;
	else
		return pA;
}
bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

void getGameFiles(string folder, vector<string> & gameFiles)
{
	WIN32_FIND_DATA search_data;
	std::wstring stemp;
	HANDLE handle;


	memset(&search_data, 0, sizeof(WIN32_FIND_DATA));

	//start with sboard files
	string sboardPath = folder + "\\*.sboard";
	stemp = std::wstring(sboardPath.begin(), sboardPath.end());
	LPCWSTR bPath = stemp.c_str();
	handle = FindFirstFile(bPath, &search_data);

	if (handle != INVALID_HANDLE_VALUE)
	{
		//check file extension
		wstring ws(search_data.cFileName);
		string filename(ws.begin(), ws.end());

		if (filename.find("sboard") != std::string::npos)
		{
			//found sboard file
			string fullPath = folder + "\\" + filename;
			gameFiles.push_back(fullPath);
		}
	}

	//start with attack-a files
	string attackAPath = folder + "\\*.attack-a";
	stemp = std::wstring(attackAPath.begin(), attackAPath.end());
	LPCWSTR attackPathA = stemp.c_str();
	handle = FindFirstFile(attackPathA, &search_data);

	if (handle != INVALID_HANDLE_VALUE)
	{
		//check file extension
		wstring ws(search_data.cFileName);
		string filename(ws.begin(), ws.end());

		if (filename.find("attack-a") != std::string::npos)
		{
			//found sboard file
			string fullPath = folder + "\\" + filename;
			gameFiles.push_back(fullPath);
		}
	}

	//start with attack-b files
	string attackBPath = folder + "\\*.attack-b";
	stemp = std::wstring(attackBPath.begin(), attackBPath.end());
	LPCWSTR attackPathB = stemp.c_str();
	handle = FindFirstFile(attackPathB, &search_data);

	if (handle != INVALID_HANDLE_VALUE)
	{
		//check file extension
		wstring ws(search_data.cFileName);
		string filename(ws.begin(), ws.end());

		if (filename.find("attack-b") != std::string::npos)
		{
			//found sboard file
			string fullPath = folder + "\\" + filename;
			gameFiles.push_back(fullPath);
		}
	}
}

bool CheckValidPath(vector<string> gameFiles, string path)
{
	bool sboard = false, attacka = false, attackb = false;
	if (gameFiles.size() == 3)
		return true;
	else
	{
		//check which file is missing and print message
		vector<string>::iterator fileIt;
		for (fileIt = gameFiles.begin(); fileIt != gameFiles.end(); ++fileIt)
		{
			if (fileIt->find("sboard") != std::string::npos)
				sboard = true;
			if (fileIt->find("attack-a") != std::string::npos)
				attacka = true;
			if (fileIt->find("attack-b") != std::string::npos)
				attackb = true;

		}
	}

	if (!sboard)
	{
		cout << "Missing board file (*.sboard) looking in path:" + path << endl;
		return false;
	}
	if (!attacka)
	{
		cout << "Missing attack file for player A (*.attack-a) looking in path:" + path << endl;
		return false;
	}
	if (!attackb)
	{
		cout << "Missing attack file for player B (*.attack-b) looking in path:" + path << endl;
		return false;
	}
	return true;
}


int PlayGame(vector<string> gameFiles)
{
	
	bool victory = false;
	int winPlayer = 2;
	char** playerBoardA = NULL;
	char** playerBoardB = NULL;
	BattleBoard* mainBoard = new BattleBoard(gameFiles[0]);
	//check board is valid and initialize board ships
	if (!mainBoard->isBoardValid())
	{
		//  invalid board
		return -1;
	}

	//create players object
	BattleshipGameAlgo* playerA = new BattleshipGameAlgo(A, gameFiles[1]);
	BattleshipGameAlgo* playerB = new BattleshipGameAlgo(B, gameFiles[2]);
	mainBoard->getPlayerBoard(playerA->playerName, playerBoardA);
	mainBoard->getPlayerBoard(playerB->playerName, playerBoardB);
	playerA->setBoard(const_cast<const char**>(playerBoardA), mainBoard->R, mainBoard->C);
	playerB->setBoard(const_cast<const char**>(playerBoardB), mainBoard->R, mainBoard->C);

	
	pair<int, int> attackMove;
	//we starts with player A
	BattleshipGameAlgo* currentPlayer = playerA;
	bool onePlayerGame = false;
	
	while (!victory)
	{
		//set current player board
		attackMove = currentPlayer->attack();
		if (attackMove.first == -1 && attackMove.second == -1)
		{
			if (onePlayerGame)
			{
				//exit while loop
				break;
			}
			onePlayerGame = true;
			currentPlayer = swapPlayer(currentPlayer, playerA, playerB);
			continue;
		}
		AttackResult moveRes = mainBoard->performGameMove(currentPlayer->playerName, attackMove);

		//notify both players on the moveAttak results
		playerA->notifyOnAttackResult(currentPlayer->playerName, attackMove.first, attackMove.second, moveRes);
		playerB->notifyOnAttackResult(currentPlayer->playerName, attackMove.first, attackMove.second, moveRes);

		//check victory:
		winPlayer = mainBoard->CheckVictory();
		if (winPlayer == A || winPlayer == B)
		{
			victory = true;
			break;
		}

		// if Miss or self hit next turn is of the other player.
		if (moveRes == AttackResult::Miss || (moveRes != AttackResult::Miss && 
			isSelfHit(currentPlayer->playerName,mainBoard->board[attackMove.first][attackMove.second]))
			currentPlayer = swapPlayer(currentPlayer, playerA, playerB);
		
	}

	if (victory)
	{
		if (winPlayer == A)
			cout << "Player A won" << endl;
		else if (winPlayer == B)
			cout << "Player B won" << endl;
	}
	//points
	cout << "Points:" << endl;
	pair<int, int> gameScore = mainBoard->CalcScore();
	cout << "Player A: " << gameScore.first << endl;
	cout << "Player B: " << gameScore.second << endl;

	//outside loop, avoid memory leak
	if (playerBoardA != NULL)
		delete[] playerBoardA;
	if (playerBoardB != NULL)
		delete[] playerBoardB;

	//delete objects
	delete playerA;
	delete playerB;
	delete mainBoard;
	return 0;
}



int main(int argc, char **argv)
{
	
	string path;
	if (argc < 2)
	{
		char the_path[256];
		//use working directory
		_getcwd(the_path, 255);
		path = std::string(the_path);
	}
	else
		path = argv[1];
	if (!dirExists(path))
	{
		std::cout << "Wrong path:" + path << endl;
		return -1;
	}
	
	//path is valid, continue
	vector<string> gameFiles;
	getGameFiles(argv[1], gameFiles);
	if (!CheckValidPath(gameFiles, path))
	{
		std::cout << "Error game files are missing, Exiting game" << endl;
		return -1;
	}

	return 	PlayGame(gameFiles);


}