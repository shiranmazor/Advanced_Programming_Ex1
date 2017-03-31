#pragma once
#include <iostream>
#include <cstring>
#include <direct.h>
#include <vector>
#include <windows.h>


using namespace std;

bool CheckValidPath(string gameFolder);
vector<string> getGameFiles(string folder);
