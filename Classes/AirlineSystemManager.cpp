#include "AirlineSystemManager.h"
#include <iostream>
using namespace std;

void AirlineSystemManager::run()
{
    FileHandler fileHandler;
    auto config = fileHandler.getConfig();
    createFlights(config);
    string input;
    while (input != "exit")
    {
        cout << "Enter command: ";
        cin >> input;
        parseCommand(input);
    }
}

void AirlineSystemManager::createFlights(const vector<tuple<string, string, int, int, vector<int>>>& allFlights)
{
    for (auto flight& : allFlights)
    {
        const string name = get<0>(flight);
        const string date = get<1>(flight);
        const int seatsPR = get<2>(flight);
        const int rows = get<3>(flight);
        const vector<int> pricing = get<4>(flight);
        flights.insert({getUID(name, date), Airplane(name, date, rows, seatsPR, pricing)});
    }
}

string AirlineSystemManager::getUID(const string& name, const string& date)
{
    return name + date;
}