#include "FileHandler.h"
#include "FileReader.h"
#include "Text.h"
#include <iostream>
#include <sstream>
#include <direct.h>

vector<tuple<string, string, int, int, vector<int>>> FileHandler::getConfig()
{
    cout << "Enter file with configuration to read: ";
    string fileName;
    cin >> fileName;
    _chdir("..");
    auto fileReader = new FileReader(&fileName);
    while (!fileReader->isOpen())
    {
        cout << "File not found! Enter file with configuration to read: ";
        cin >> fileName;
        delete fileReader;
        fileReader = new FileReader(&fileName);
    }
    const string fileContent = fileReader->getData();
    cout << "File read successfully!" << endl;
    auto flights = parseArguments(fileContent);
    return flights;
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
        flightInfo.erase(flightInfo.begin(), flightInfo.begin() + 3);
        string info;
        for (string& s : flightInfo)
            info += s + " ";
        int rows = 0;
        vector<int> pricing = parseRows(info, rows);
        allFlights.emplace_back(name, date, seatsPR, rows, pricing);
    }
    return allFlights;
}

vector<int> FileHandler::parseRows(const string& info, int& lastRow)
{
    vector<int> prices;
    stringstream ss(info);
    string rowPart, pricePart;
    prices.push_back(0); // For row 0

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
        int price = stoi(pricePart);
        for (int i = startRow; i <= endRow; ++i)
        {
            prices.push_back(price);
        }
    }

    prices.resize(lastRow + 1);
    return prices;
}
