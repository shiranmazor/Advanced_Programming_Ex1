#pragma once
#include <iostream>
#include <cstring>
#include <direct.h>
#include <vector>
#include <windows.h>


using namespace std;

bool CheckValidPath(string gameFolder);
void getGameFiles(string folder, vector<string> & gameFiles);
