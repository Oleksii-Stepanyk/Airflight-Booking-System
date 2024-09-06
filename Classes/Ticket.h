#pragma once
#include <string>
using namespace std;

class Ticket {
    string id;
    string username;
    string seat;
    int price;
    string bookingStatus;
public:
    Ticket(string, string, string, int, string);
};