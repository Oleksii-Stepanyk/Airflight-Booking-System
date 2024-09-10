#include "Ticket.h"

Ticket::Ticket() : id(0), username(""), flightNo(""), date(""), seat(""), price(""), bookingStatus("")
{
}

Ticket::Ticket(const string& myID, const string& name, const string& flight, const string& flightDate,
               const string& place, const string& ticketPrice,
               const string& status)
    : id(myID), username(name), flightNo(flight), date(flightDate), seat(place), price(ticketPrice),
      bookingStatus(status)
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
