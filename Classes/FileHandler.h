#pragma once
#include <string>
#include <map>
#include "Airplane.h"
using namespace std;

class FileHandler
{
public:
    static vector<tuple<string, string, int, int, vector<int>>> getConfig();
    static string readFile(const string&);
    static vector<int> parseRows(const string&, int&);
    static vector<tuple<string, string, int, int, vector<int>>> parseArguments(const string&);
};
