#pragma once
#include <iostream>
#include <cstring>
#include <direct.h>
#include <vector>
#include <windows.h>


using namespace std;

bool CheckValidPath(vector<string> gameFiles);
void getGameFiles(string folder, vector<string> & gameFiles);

