#include "AirlineSystemManager.h"
#include "FileHandler.h"
#include "Text.h"
#include <iostream>
#include <ranges>
using namespace std;

void AirlineSystemManager::run()
{
    const auto config = FileHandler::getConfig();
    createFlights(config);
    string input;
    cin.ignore();
    while (input != "exit")
    {
        cout << "Enter command: ";
        getline(cin, input);
        parseCommand(input);
    }
}

void AirlineSystemManager::createFlights(const vector<tuple<string, string, int, int, vector<int>>>& flights)
{
    for (auto& flight : flights)
    {
        string name = get<0>(flight);
        string date = get<1>(flight);
        int seatsPR = get<2>(flight);
        int rows = get<3>(flight);
        vector<int> pricing = get<4>(flight);
        Airplane airplane(&name, &date, &seatsPR, &rows, &pricing);
        allFlights.insert({getFlightID(name, date), airplane});
    }
    cout << "Flights added successfully!" << endl;
}

string AirlineSystemManager::getFlightID(const string& name, const string& date)
{
    hash<string> hasher;
    return to_string(hasher(name + date));
}

void AirlineSystemManager::parseCommand(const string& command)
{
    const vector<string> args = Text::split(command, ' ');
    if (args.empty())
    {
        cout << "Invalid command!" << endl;
        return;
    }
    if (const string& action = Text::to_lower(args[0]); action == "exit")
    {
        return;
    }
    else if (action == "check" && args.size() == 3)
    {
        checkSeats(Text::to_upper(args[1]), args[2]);
    }
    else if (action == "book" && args.size() == 5)
    {
        bookTicket(args[1], Text::to_upper(args[2]), Text::to_upper(args[3]), args[4]);
    }
    else if (action == "return" && args.size() == 2)
    {
        returnTicket(args[1]);
    }
    else if (action == "view" && args.size() >= 3)
    {
        if (const string& type = Text::to_lower(args[1]); type == "ticket" && args.size() == 3)
        {
            viewTicket(args[2]);
        }
        else if (type == "user" && args.size() == 3)
        {
            viewUser(args[2]);
        }
        else if (type == "flight" && args.size() == 4)
        {
            viewFlight(args[2], Text::to_upper(args[3]));
        }
        else
        {
            cout << "Invalid command!" << endl;
        }
    }
    else
    {
        cout << "Invalid command!" << endl;
    }
}

void AirlineSystemManager::checkSeats(const string& name, const string& date)
{
    const string& uid = getFlightID(name, date);
    if (!allFlights.contains(uid))
    {
        cout << "Flight not found!" << endl;
        return;
    }
    allFlights[uid].availableSeats();
}

void AirlineSystemManager::bookTicket(const string& date, const string& flightNo, const string& place,
                                      const string& username)
{
    const string& uid = getFlightID(flightNo, date);
    if (!allFlights.contains(uid))
    {
        cout << "Flight not found!" << endl;
        return;
    }
    Airplane& flight = allFlights[uid];
    if (!flight.isSeatBooked(place))
    {
        string row = place;
        row.pop_back();
        string ticketID = to_string(lastTicketID + 1);
        lastTicketID++;
        string price = to_string(flight.getPrice(stoi(row))) + "$";
        string status = "booked";
        Ticket ticket(&ticketID, &username, &flightNo, &date, &place, &price, &status);
        flight.addSeat(place);
        cout << "Ticket added with ID " << ticketID << endl;
        allTickets.insert({ticketID, ticket});
    }
    else
    {
        cout << "Ticket already booked!" << endl;
    }
}

void AirlineSystemManager::returnTicket(const string& ticketID)
{
    if (!allTickets.contains(ticketID))
    {
        cout << "Ticket not found!" << endl;
        return;
    }
    Ticket ticket = allTickets[ticketID];
    ticket.changeStatus("Returned");
    Airplane flight = allFlights[getFlightID(ticket.getFlightNo(), ticket.getDate())];
    flight.removeSeat(ticket.getSeat());
    allTickets.erase(ticketID);
    cout << "Confirmed refund " << ticket.getPrice() << " for " << ticket.getUsername() << endl;
}

void AirlineSystemManager::viewTicket(const string& ticketID)
{
    if (!allTickets.contains(ticketID))
    {
        cout << "Ticket not found!" << endl;
        return;
    }
    Ticket ticket = allTickets[ticketID];
    cout << "Flight " << ticket.getFlightNo() << ", " << ticket.getDate() << ", seat " << ticket.getSeat() << ", price "
        << ticket.getPrice() << ", " << ticket.getUsername() << endl;
}

void AirlineSystemManager::viewUser(const string& username)
{
    int i = 1;
    for (auto& ticket : allTickets | views::values)
    {
        if (ticket.getUsername() == username)
        {
            cout << i << ". Flight " << ticket.getFlightNo() << ", " << ticket.getDate() << ", seat " << ticket.
                getSeat() << ", price "
                << ticket.getPrice() << endl;
            i++;
        }
    }
}

void AirlineSystemManager::viewFlight(const string& date, const string& flightNo)
{
    string uid = getFlightID(flightNo, date);
    if (!allFlights.contains(uid))
    {
        cout << "Flight not found!" << endl;
        return;
    }
    Airplane flight = allFlights[uid];
    vector<string> bookedSeats = flight.getBookedSeats();
    for (const string& seat : bookedSeats)
    {
        for (auto& ticket : allTickets | views::values)
        {
            if (ticket.getDate() == date && ticket.getFlightNo() == flightNo && ticket.getSeat() == seat)
            {
                cout << ticket.getSeat() << " " << ticket.getUsername() << " " << ticket.getPrice() << endl;
                break;
            }
        }
    }
}
