#include "BattleshipGameAlgo.h"
#include "Game.h"
#include <algorithm>

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

}
void getFilesList(string filePath, string extension, vector<string> & returnFileName)
{
	WIN32_FIND_DATA fileInfo;
	HANDLE hFind;
	string  fullPath = filePath + extension;
	hFind = FindFirstFile(fullPath.c_str(), &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE) {
		returnFileName.push_back(filePath + fileInfo.cFileName);
		while (FindNextFile(hFind, &fileInfo) != 0) {
			returnFileName.push_back(filePath + fileInfo.cFileName);
		}
	}
}


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		//search files in working directory
	}
	else
	{
		
	}
	

}