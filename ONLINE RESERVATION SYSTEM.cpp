#include <iostream>
#include <string>

using namespace std;
const int MAX_RESERVATIONS = 100;
bool validateLogin(const string& username, const string& password) {
   
		if (username == "user" && password == "1234"){ 
		//in real world applications we can change these accordingly and check with the database 
		return true;
	}
	else {
		return false;
	}
}


struct Reservation {
    int PNR;
    string name;
    string trainNumber;
    string trainName;
    string classType;
    string dateOfJourney;
    string from;
    string to;
    string status;
};

void displayReservation(const Reservation& res) {
   if (res.status == "canceled") {
        cout << "PNR: " << res.PNR << " (Canceled)" << endl;
        cout << "Name: " << res.name << endl;
        cout << "Status: Canceled" << endl;
        cout << endl;
    } else {
        cout << "PNR: " << res.PNR << endl;
        cout << "Name: " << res.name << endl;
        cout << "Train Number: " << res.trainNumber << endl;
        cout << "Train Name: " << res.trainName << endl;
        cout << "Class Type: " << res.classType << endl;
        cout << "Date of Journey: " << res.dateOfJourney << endl;
        cout << "From: " << res.from << endl;
        cout << "To: " << res.to << endl;
        cout << "Ticket booked succesfully..!"<<endl;
        cout << endl;
    }
}

void displayAllReservations(Reservation reservations[], int numReservations) {
    if (numReservations == 0) {
        cout << "No reservations to display. The reservation list is empty." << endl;
        return;
    }

    cout << "===== All Reservations =====" << endl;
    for (int i = 0; i < numReservations; i++) {
        displayReservation(reservations[i]);
    }
}


bool makeReservation(Reservation reservations[], int& numReservations) {
    if (numReservations == MAX_RESERVATIONS) {
        cout << "Sorry, reservations are full." << endl;
        return false;
    }

    Reservation newRes;
    newRes.PNR = numReservations + 1;

    cout << "Enter Name: ";
//    cin.ignore();
    getline(cin, newRes.name);

    cout << "Enter Train Number: ";
    getline(cin, newRes.trainNumber);

    cout << "Enter Train Name: ";
    getline(cin, newRes.trainName);

    cout << "Enter Class Type: ";
    getline(cin, newRes.classType);

    cout << "Enter Date of Journey: ";
    getline(cin, newRes.dateOfJourney);

    cout << "Enter From (Place): ";
    getline(cin, newRes.from);

    cout << "Enter To (Destination): ";
    getline(cin, newRes.to);

    reservations[numReservations] = newRes;
    numReservations++;

    cout << "Reservation Successful! Your PNR: " << newRes.PNR << endl;
    return true;
}


bool cancelReservation(Reservation reservations[], int& numReservations) {
    if (numReservations == 0) {
        cout << "No reservations to cancel. The reservation list is empty." << endl;
        return false;
    }

    cout << "Enter PNR to cancel reservation: ";
    int pnrToCancel;
    cin >> pnrToCancel;
    cin.ignore();

    for (int i = 0; i < numReservations; i++) {
        if (reservations[i].PNR == pnrToCancel) {
            if (reservations[i].status == "canceled") {
                cout << "This reservation is already canceled." << endl;
                return false;
            }   
		    cout << "Reservation Details:" << endl;
            displayReservation(reservations[i]);
		reservations[i].status="active";
            cout << "Press 'OK' to confirm cancellation or 'N' to go back: ";
            string confirm;
            cin>>confirm;

            if (confirm == "OK" || confirm == "ok" || confirm == "Ok") {
                reservations[i].status="canceled";             
                cout << "Reservation Canceled Successfully!" << endl;
                return true;
            } else {
                cout << "Cancellation Canceled!" << endl;
                return true;
            }
        }
    }

    cout << "No reservation found with the given PNR." << endl;
    return false;
}



int main() {
    string username, password,opt;
    cout << "===== Login Form =====" << endl;

    while (true) {
        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        if (validateLogin(username, password)) {
            cout << "Login successful! Welcome, " << username << "!" << endl;
            break;
        } else {
            cout << "Invalid credentials. Please try again." << endl;
        }
    }

    Reservation reservations[MAX_RESERVATIONS];
    int numReservations = 0;

    if (validateLogin(username, password)) {
        cout << "Enter the number of tickets : ";
        int numTicketsReservations;
        cin >> numTicketsReservations;
        cin.ignore(); // Clear the newline character from the input buffer

        for (int i = 0; i < numTicketsReservations; i++) {
            makeReservation(reservations, numReservations);
        }
	cout<<"Do you want to cancel any of these tickets ? (Y/N)\n";
	cin>>opt;
	        if (opt == "Y" || opt == "y" || opt == "yes" || opt == "Yes" || opt == "YES") {

		cout << "How many tickets you want to cancel ?\t";
    int numTicketsCancellations;
    cin >> numTicketsCancellations;

    for (int i = 0; i < numTicketsCancellations; i++) {
        cancelReservation(reservations, numReservations);
    }
}
    displayAllReservations(reservations, numReservations);

    }

    return 0;
}

