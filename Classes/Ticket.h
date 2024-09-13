#pragma once
#include <string>
using namespace std;

class Ticket
{
    const string id;
    const string username;
    const string flightNo;
    const string date;
    const string seat;
    const string price;
    string bookingStatus;

public:
    Ticket();
    Ticket(string*, const string*, const string*, const string*, const string*, const string*, string*);
    string getSeat();
    string getDate();
    string getFlightNo();
    string getPrice();
    string getUsername();
    void changeStatus(const string&);
};
