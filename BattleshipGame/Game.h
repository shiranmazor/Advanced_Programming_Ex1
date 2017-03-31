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
void PlayGame(vector<string> gameFiles);


