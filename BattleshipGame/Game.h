#pragma once
#include <iostream>
#include <cstring>
#include <windows.h>
#include <vector>
using namespace std;


bool CheckValidPath(string gameFolder);
int CalcScore(char** board);
string CheckVictory(char** board);
bool isBoardValid(char** board);
char** readBoard(string boardPath);
void getGameFiles(string folder, vector<string> & gameFiles);
