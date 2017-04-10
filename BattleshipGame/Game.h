#pragma once
#include <iostream>
#include <string>
#include <direct.h>
#include <vector>
#include <windows.h>
#include <stdio.h>



using namespace std;

bool CheckValidPath(vector<string> gameFiles, string path);
void getGameFiles(string folder, vector<string> & gameFiles);
bool dirExists(const std::string& dirName_in);
/*
* performing game steps and finish the game in case of victory or finished attack steps
* gameFiles contains - sboard file, attack-a file,attack-b file by this order!
*/
int PlayGame(vector<string> gameFiles);


