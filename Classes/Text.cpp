#include "Text.h"
#include <sstream>

vector<string> Text::split(const string& str, const char& delimiter)
{
    vector<string> result;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delimiter))
    {
        result.push_back(item);
    }
    return result;
}

string Text::to_lower(const string& str)
{
    string result = str;
    for (char& c : result)
    {
        c += 32 * (c >= 'A' && c <= 'Z');
    }
    return result;
}

string Text::to_upper(const string& str)
{
    string result = str;
    for (char& c : result)
    {
        c = c - 32 * (c >= 'a' && c <= 'z');
    }
    return result;
}