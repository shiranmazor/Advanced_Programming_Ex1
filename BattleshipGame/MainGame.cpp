#include "BattleshipGameAlgo.h"
#include "Game.h"

/*
 * get current working directory path
 */
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
	bool sboard=false, attacka=false, attackb=false;
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


void PlayGame(vector<string> gameFiles)
{
	//we starts with player A
	Player currentPlayer = A;
	bool gameOver = false;

	BattleBoard* mainBoard = new BattleBoard(gameFiles[0]);
	//create players object
	BattleshipGameAlgo* playerA = new BattleshipGameAlgo(A, gameFiles[1]);
	BattleshipGameAlgo* playerB = new BattleshipGameAlgo(A, gameFiles[1]);
	  
	char** playerBoard = NULL;
	pair<int, int> attackMove;
	while (!gameOver)
	{
		//set current player board
		mainBoard->getPlayerBoard(currentPlayer, playerBoard);
		if (currentPlayer == A)
		{
			//set board to playerA
			playerA->setBoard(const_cast<const char**>(playerBoard), mainBoard->R, mainBoard->C);
			//get attack move
			attackMove = playerA->attack();

			//Todo:perform move
			AttackResult moveRes = mainBoard->performGameMove(playerA->playerName, attackMove);

			//notify both players on the moveAttak results
			playerA->notifyOnAttackResult(A, attackMove.first, attackMove.second, moveRes);
			playerB->notifyOnAttackResult(A, attackMove.first, attackMove.second, moveRes);
			//Todo:check if playerA hit\sink then give another turn else swap players
		}			
		else
		{
			//set board to playerB
			playerB->setBoard(const_cast<const char**>(playerBoard), mainBoard->R, mainBoard->C);
			//get attack move
			attackMove = playerB->attack();
			//Todo:perform move

			AttackResult moveRes = mainBoard->performGameMove(playerB->playerName, attackMove);

			//notify both players on the moveAttak results
			playerA->notifyOnAttackResult(B, attackMove.first, attackMove.second, moveRes);
			playerB->notifyOnAttackResult(B, attackMove.first, attackMove.second, moveRes);
			//Todo:check if playerA hit\sink then give another turn else swap players
		}

		
	}
	
	if (playerBoard != NULL)
		delete playerBoard;//avoid memory leak
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
		cout << "Wrong path:" + path << endl;
		return -1;
	}
	//path is valid, continue
	vector<string> gameFiles;
	getGameFiles(argv[1], gameFiles);
	if (!CheckValidPath(gameFiles,path))
	{
		cout << "Error game files are missing, Exiting game" << endl;
		return -1;
	}
	
	PlayGame(gameFiles);

	
}