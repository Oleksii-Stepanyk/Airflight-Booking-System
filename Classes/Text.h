#pragma once
#include <string>
#include <vector>
using namespace std;

class Text
{
public:
    static vector<string> split(const string&, const char&);
    static string to_lower(const string&);
    static string to_upper(const string&);
};
