#include "FileHandler.h"
#include "Text.h"
#include <iostream>
#include <fstream>
#include <ranges>
#include <sstream>
#include <direct.h>

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
    _chdir("..");
    fstream file(fileName);
    string fileContent, line;
    while (getline(file, line))
        fileContent += line + "\n";
    file.close();
    return fileContent;
}

vector<tuple<string, string, int, int, vector<int>>> FileHandler::parseArguments(const string& args)
{
    vector<tuple<string, string, int, int, vector<int>>> allFlights;
    for (vector<string> flights = Text::split(args, '\n'); string& flight : flights)
    {
        vector<string> flightInfo = Text::split(flight, ' ');
        string date = flightInfo[0];
        string name = flightInfo[1];
        int seatsPR = stoi(flightInfo[2]);
        flightInfo.erase(flightInfo.begin(), flightInfo.begin() + 2);
        int rows = 0;
        vector<int> pricing = parseInfo(flightInfo, rows);
        allFlights.push_back(make_tuple(name, date, seatsPR, rows, pricing));
    }
    return allFlights;
}

vector<int> FileHandler::parseInfo(const vector<string>& info, int& lastRow)
{
    vector<int> prices;
    for (const auto& part : info)
    {
        stringstream ss(part);
        string rowPart, pricePart;

        while (ss >> rowPart >> pricePart)
        {
            int startRow, endRow;
            if (const size_t dashPos = rowPart.find('-'); dashPos != string::npos)
            {
                startRow = stoi(rowPart.substr(0, dashPos));
                endRow = stoi(rowPart.substr(dashPos + 1));
            }
            else
            {
                startRow = endRow = stoi(rowPart);
            }

            lastRow = max(lastRow, endRow);

            pricePart.pop_back();
            int price = std::stoi(pricePart);

            for (int i = startRow; i <= endRow; ++i)
            {
                prices[i] = price;
            }
        }
    }
    prices.resize(lastRow + 1);
    return prices;
}
