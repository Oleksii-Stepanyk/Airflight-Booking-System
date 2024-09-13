#include "Airplane.h"
#include <map>
#include <algorithm>
#include <iostream>

Airplane::Airplane(string* planeName, string* flightDate, int* seatsPR, int* totalRows,
                   vector<int>* pricing)
    : name(*planeName), date(*flightDate), seatsPerRow(*seatsPR), rows(*totalRows), pricingInfo(*pricing)
{
}

Airplane::Airplane() : seatsPerRow(0), rows(0), pricingInfo({})
{
}

void Airplane::availableSeats()
{
    map<int, char> seats;
    for (int i = 1; i <= seatsPerRow; i++)
    {
        seats.insert({i, 64 + i});
    }
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j <= seatsPerRow; j++)
        {
            if (bookedSeats.empty() || ranges::find(bookedSeats, to_string(i) + seats[j]) == bookedSeats.end())
            {
                cout << i << seats[j] << " " << pricingInfo[i] << "$ ";
            }
        }
        cout << endl;
    }
}

void Airplane::addSeat(const string& seat)
{
    bookedSeats.push_back(seat);
}

void Airplane::removeSeat(const string& seat)
{
    bookedSeats.erase(ranges::find(bookedSeats, seat));
}

bool Airplane::isSeatBooked(const string& place)
{
    return ranges::find(bookedSeats, place) != bookedSeats.end();
}

int Airplane::getPrice(const int& row)
{
    return pricingInfo[row];
}

vector<string> Airplane::getBookedSeats()
{
    return bookedSeats;
}
