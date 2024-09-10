#pragma once
#include <string>
#include <vector>
#include <map>
#include "Ticket.h"
using namespace std;

class Airplane
{
    const string name;
    const string date;
    const int seatsPerRow;
    const int rows;
    const vector<int> pricingInfo;
    map<string, Ticket> bookedTickets;

public:
    Airplane();
    Airplane(const string&, const string&, int, int, const vector<int>&);
    void availableSeats();
    void addTicket(Ticket&);
    int getPrice(const int&);
    bool isSeatBooked(const string&);
};
