#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <ranges>
#include <sstream>

vector<tuple<string, string, int, int, vector<int>>> FileHandler::getConfig()
{
    cout << "Enter file with configuration to read: ";
    string filename;
    cin >> filename;
    const string args = readFile(filename);
    cout << "File read successfully!" << endl;
    auto flights = parseArguments(args);
    return flights;
}

string FileHandler::readFile(const string& fileName)
{
    fstream file(fileName);
    string fileContent;
    while (file.is_open())
        file >> fileContent;
    file.close();
    return fileContent;
}

vector<string> FileHandler::splitText(const string& str, const char& delimiter)
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

vector<tuple<string, string, int, int, vector<int>>> FileHandler::parseArguments(const string& args)
{
    for (vector<string> flights = splitText(args, '\n'); string flight& : flights)
    {
        vector<string> flightInfo = splitText(flight, ' ');
        string name = flightInfo[0];
        string date = flightInfo[1];
        //unfinished
    }
}
