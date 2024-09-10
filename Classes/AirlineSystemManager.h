#pragma once
#include <string>
#include <vector>
#include <map>
#include "Airplane.h"
#include "FileHandler.h"
using namespace std;

class AirlineSystemManager
{
    FileHandler fileHandler;
    map<string, Airplane> flights;
    map<string, vector<Ticket>> allTicketsByUser;
    map<string, Ticket> allTicketsByID;
    int lastTicketID = 10099;

public:
    void run();
    void createFlights(const vector<tuple<string, string, int, int, vector<int>>>&);
    static string getFlightID(const string&, const string&);
    void parseCommand(const string&);
    void checkSeats(const string&, const string&);
    void bookTicket(const string&, const string&, const string&, const string&);
    void returnTicket(const string&);
    void viewTicket(const string&);
    void viewUser(const string&);
    void viewFlight(const string&, const string&);
};
