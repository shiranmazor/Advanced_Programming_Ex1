#include "BattleshipGameAlgo.h"
#include "Game.h"

std::string getexepath()
{
	char result[MAX_PATH];
	wchar_t wtext[MAX_PATH];
	mbstowcs(wtext, result, strlen(result) + 1);//Plus null
	LPWSTR ptr = wtext;
	return std::string(result, GetModuleFileName(NULL, ptr, MAX_PATH));
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

	//start with attack-a files
	string attackBPath = folder + "\\*.attack-b";
	stemp = std::wstring(attackAPath.begin(), attackAPath.end());
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

bool CheckValidPath(vector<string> gameFiles)
{
	return true;
}



int main(int argc, char **argv)
{
	string path;
	if (argc < 2)
	{
		//search files in working directory
		path = getexepath();
	}
	else
	{
		path = argv[1];
	}
	vector<string> gameFiles;
	getGameFiles(argv[1], gameFiles);
	if (!CheckValidPath(gameFiles))
	{
		cout << "Error game files are missing, exiting game" << endl;
		return -1;
	}

	
}