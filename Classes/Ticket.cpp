#include "Ticket.h"

Ticket::Ticket() = default;

Ticket::Ticket(string* myID, const string* name, const string* flight, const string*flightDate,
               const string* place, const string* ticketPrice,
               string* status)
    : id(*myID), username(*name), flightNo(*flight), date(*flightDate), seat(*place), price(*ticketPrice),
      bookingStatus(*status)
{
}

string Ticket::getDate()
{
    return date;
}

string Ticket::getFlightNo()
{
    return flightNo;
}

string Ticket::getSeat()
{
    return seat;
}

string Ticket::getPrice()
{
    return price;
}

string Ticket::getUsername()
{
    return username;
}


void Ticket::changeStatus(const string& status)
{
    bookingStatus = status;
}
