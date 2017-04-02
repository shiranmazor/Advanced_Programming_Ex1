#include "Common.h"
#include <algorithm>

std::vector<std::string> splitString(std::string str, char c)
{
	std::stringstream test(str);
	std::string segment;
	std::vector<std::string> seglist;

	while (std::getline(test, segment, c))
	{
		seglist.push_back(segment);
	}
	return seglist;
}

void replaceAll(string &str, const string &search, const string &replace) 
{
	for (size_t pos = 0; ; pos += replace.length()) 
	{
		// Locate the substring to replace
		pos = str.find(search, pos);
		if (pos == string::npos) break;
		// Replace by erasing and inserting
		str.erase(pos, search.length());
		str.insert(pos, replace);
	}
}

string removeSpaces(string input)
{
	input.erase(remove_if(input.begin(), input.end(), isspace), input.end());
	return input;
}