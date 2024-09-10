#pragma once
#include <string>
using namespace std;

class Ticket
{
    const string id;
    const string username;
    const string seat;
    const string price;
    string bookingStatus;

public:
    Ticket(const string&, const string&, const string&, const string&, const string&);
    string getSeat();
    void changeStatus(const string&);
};
