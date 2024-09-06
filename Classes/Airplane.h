#pragma once
#include <string>
#include <vector>
#include "Ticket.h"
using namespace std;

class Airplane {
    const string name;
    const string date;
    const int seatsPerRow;
    const int rows;
    vector<int> pricingInfo;
    vector<Ticket> bookedTickets;
public:
    Airplane(const string&, const string&, const int&, const int&, const vector<int>&);
};