#pragma once
#include <string>
#include <map>
#include "Airplane.h"
using namespace std;

class FileHandler
{
public:
    vector<tuple<string, string, int, int, vector<int>>> getConfig();
    string readFile(const string&);
    vector<int> parseInfo(const vector<string>&, int&);
    vector<tuple<string, string, int, int, vector<int>>> parseArguments(const string&);
};
