#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Flight {
private:
    string flightNumber;
    string departure;
    string arrival;
    int capacity;
    int bookedSeats;
    vector<string> passengerIDs;

public:
    Flight(string num, string dep, string arr, int cap) 
        : flightNumber(num), departure(dep), arrival(arr), capacity(cap), bookedSeats(0) {}

    bool bookSeat(const string& passengerID) {
        if (bookedSeats >= capacity) {
            return false;
        }
        passengerIDs.push_back(passengerID);
        bookedSeats++;
        return true;
    }

    bool cancelSeat(const string& passengerID) {
        for (auto it = passengerIDs.begin(); it != passengerIDs.end(); ++it) {
            if (*it == passengerID) {
                passengerIDs.erase(it);
                bookedSeats--;
                return true;
            }
        }
        return false;
    }

    bool upgradeSeat(const string& passengerID) {
        for (auto& id : passengerIDs) {
            if (id == passengerID) {
                return true;
            }
        }
        return false;
    }

    string getFlightNumber() const { return flightNumber; }
    string getDeparture() const { return departure; }
    string getArrival() const { return arrival; }
    int getCapacity() const { return capacity; }
    int getBookedSeats() const { return bookedSeats; }
};

class Passenger {
private:
    string ID;
    string name;

public:
    Passenger(string id, string n) : ID(id), name(n) {}

    bool requestBooking(Flight& flight) {
        return flight.bookSeat(ID);
    }

    bool requestCancellation(Flight& flight) {
        return flight.cancelSeat(ID);
    }

    bool requestUpgrade(Flight& flight) {
        return flight.upgradeSeat(ID);
    }

    string getID() const { return ID; }
    string getName() const { return name; }
};

int main() {
    Flight pk301("PK301", "Karachi", "Lahore", 150);
    Flight pk702("PK702", "Islamabad", "Dubai", 200);

    Passenger ali("42101-1234567-1", "Ali Khan");
    Passenger sana("35202-7654321-6", "Sana Ahmed");
    Passenger usman("12345-6789012-3", "Usman Malik");

    cout << "Booking seats:\n";
    cout << "Ali's booking: " << (ali.requestBooking(pk301) ? "Success" : "Failed") << endl;
    cout << "Sana's booking: " << (sana.requestBooking(pk301) ? "Success" : "Failed") << endl;
    cout << "Usman's booking: " << (usman.requestBooking(pk702) ? "Success" : "Failed") << endl;

    cout << "\nFlight status:\n";
    cout << "PK301 bookings: " << pk301.getBookedSeats() << "/" << pk301.getCapacity() << endl;
    cout << "PK702 bookings: " << pk702.getBookedSeats() << "/" << pk702.getCapacity() << endl;

    cout << "\nCancelling seats:\n";
    cout << "Ali's cancellation: " << (ali.requestCancellation(pk301) ? "Success" : "Failed") << endl;

    cout << "\nUpgrading seats:\n";
    cout << "Sana's upgrade: " << (sana.requestUpgrade(pk301) ? "Success" : "Failed") << endl;
    
    // Uncommenting below will cause compilation errors due to private members
    // pk301.capacity--;
    // pk301.bookedSeats = 0;

    return 0;
}