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
