#include "AirlineSystemManager.h"

#include <chrono>

#include "Text.h"
#include <iostream>
using namespace std;

void AirlineSystemManager::run()
{
    FileHandler fileHandler;
    const auto config = fileHandler.getConfig();
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

void AirlineSystemManager::createFlights(const vector<tuple<string, string, int, int, vector<int>>>& allFlights)
{
    for (auto& flight : allFlights)
    {
        string name = get<0>(flight);
        string date = get<1>(flight);
        int seatsPR = get<2>(flight);
        int rows = get<3>(flight);
        vector<int> pricing = get<4>(flight);
        Airplane airplane(name, date, seatsPR, rows, pricing);
        flights.insert({getFlightID(name, date), airplane});
    }
    cout << "Flights added successfully!" << endl;
}

string AirlineSystemManager::getFlightID(const string& name, const string& date)
{
    return name + date;
}

void AirlineSystemManager::parseCommand(const string& command)
{
    const vector<string> args = Text::split(command, ' ');
    if (args.empty())
    {
        cout << "Invalid command!" << endl;
        return;
    }

    if (const string& action = args[0]; action == "check" && args.size() == 3)
    {
        checkSeats(args[1], args[2]);
    }
    else if (action == "book" && args.size() == 5)
    {
        bookTicket(args[1], args[2], args[3], args[4]);
    }
    else if (action == "return" && args.size() == 2)
    {
        returnTicket(args[1]);
    }
    else if (action == "view" && args.size() >= 3)
    {
        if (const string& type = args[1]; type == "ticket" && args.size() == 3)
        {
            viewTicket(args[2]);
        }
        else if (type == "user" && args.size() == 3)
        {
            viewUser(args[2]);
        }
        else if (type == "flight" && args.size() == 4)
        {
            viewFlight(args[2], args[3]);
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
    if (!flights.contains(uid))
    {
        cout << "Flight not found!" << endl;
        return;
    }
    flights[uid].availableSeats();
}

void AirlineSystemManager::bookTicket(const string& date, const string& flightNo, const string& place,
                                      const string& username)
{
    const string& uid = getFlightID(flightNo, date);
    if (!flights.contains(uid))
    {
        cout << "Flight not found!" << endl;
        return;
    }
    Airplane flight = flights[uid];
    if (!flight.isSeatBooked(place))
    {
        string row = place;
        row.pop_back();
        string ticketID = to_string(lastTicketID + 1);
        lastTicketID++;
        string price = to_string(flight.getPrice(stoi(row))) + "$";
        Ticket ticket(ticketID, username, flightNo, date, place, price, "booked");
        flight.addTicket(ticket);
        cout << "Ticket added with ID " << ticketID << endl;
        if (!allTicketsByUser.contains(username))
        {
            vector<Ticket> userTickets;
            userTickets.push_back(ticket);
            allTicketsByUser.insert({username, userTickets});
        }
        else
        {
            allTicketsByUser[username].push_back(ticket);
        }
        allTicketsByID.insert({ticketID, ticket});
    }
    else
    {
        cout << "Ticket already booked!" << endl;
    }
}

void AirlineSystemManager::returnTicket(const string& ticketID)
{
    if (!allTicketsByID.contains(ticketID))
    {
        cout << "Ticket not found!" << endl;
        return;
    }
    Ticket ticket = allTicketsByID[ticketID];
    ticket.changeStatus("Returned");
    Airplane flight = flights[getFlightID(ticket.getFlightNo(), ticket.getDate())];
    flight.removeTicket(ticket);
    allTicketsByID.erase(ticketID);
    cout << "Confirmed refund " << ticket.getPrice() << " for " << ticket.getUsername() << endl;
}

void AirlineSystemManager::viewTicket(const string& ticketID)
{
    if (!allTicketsByID.contains(ticketID))
    {
        cout << "Ticket not found!" << endl;
        return;
    }
    Ticket ticket = allTicketsByID[ticketID];
    cout << "Flight " << ticket.getFlightNo() << ", " << ticket.getDate() << ", seat " << ticket.getSeat() << ", price "
        << ticket.getPrice() << ", " << ticket.getUsername() << endl;
}

void AirlineSystemManager::viewUser(const string& username)
{
    if (!allTicketsByUser.contains(username))
    {
        cout << "Ticket not found!" << endl;
        return;
    }
    vector<Ticket> tickets = allTicketsByUser[username];
    for (int i = 0; i < tickets.size(); i++)
    {
        cout << i + 1 << ". Flight " << tickets[i].getFlightNo() << ", " << tickets[i].getDate() << ", seat " << tickets
            [i].getSeat() << ", price "
            << tickets[i].getPrice() << endl;
    }
}

void AirlineSystemManager::viewFlight(const string& date, const string& flightNo)
{
    string uid = getFlightID(flightNo, date);
    if (!flights.contains(uid))
    {
        cout << "Flight not found!" << endl;
        return;
    }
    Airplane flight = flights[uid];
    flight.showBookedSeats();
}
