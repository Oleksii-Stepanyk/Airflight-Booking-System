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
    vector<string> bookedSeats;

public:
    Airplane();
    Airplane(string*, string*, int*, int*, vector<int>*);
    void availableSeats();
    void addSeat(const string&);
    void removeSeat(const string&);
    vector<string> getBookedSeats();
    int getPrice(const int&);
    bool isSeatBooked(const string&);
};
