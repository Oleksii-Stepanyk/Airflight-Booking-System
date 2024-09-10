#include "Airplane.h"
#include <map>
#include <algorithm>
#include <iostream>

Airplane::Airplane(const string& planeName, const string& flightDate, int seatsPR, int totalRows,
                   const vector<int>& pricing)
    : name(planeName), date(flightDate), seatsPerRow(seatsPR), rows(totalRows), pricingInfo(pricing)
{
}

Airplane::Airplane() : name(""), date(""), seatsPerRow(0), rows(0), pricingInfo({})
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
            if (bookedTickets.empty() || !bookedTickets.contains(to_string(i) + seats[j]))
            {
                cout << i << seats[j] << " " << pricingInfo[i] << "$ ";
            }
        }
    }
}

void Airplane::addTicket(Ticket& ticket)
{
    bookedTickets.insert({ticket.getSeat(), ticket});
}

bool Airplane::isSeatBooked(const string& place)
{
    return bookedTickets.contains(place);
}

int Airplane::getPrice(const int& row)
{
    return pricingInfo[row];
}
