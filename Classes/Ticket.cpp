#include "Ticket.h"

Ticket::Ticket(const string& myID, const string& name, const string& place, const string& ticketPrice,
               const string& status>)
    : id(myID), username(name), seat(place), price(ticketPrice), bookingStatus(status)
{
}

string Ticket::getSeat()
{
    return seat;
}

void Ticket::changeStatus(const string& status)
{
    bookingStatus = status;
}
