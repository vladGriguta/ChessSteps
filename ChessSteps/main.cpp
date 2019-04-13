#include <exception>

#include "session.h"

int main()
{
	// First initialize the board
	session newSession;
	string initializeNewSession = "";

	while (initializeNewSession != "y" || initializeNewSession != "n"){
		cout << "Would you like to play some chess? (y/n)\n";
		cin >> initializeNewSession;
		if (initializeNewSession == "y"){
			newSession.initialize();
			newSession.runSession();
			initializeNewSession = "";
		}
		else if (initializeNewSession == "n"){
			cout << "\n=======================================================\n";
			cout << "===============Thank you for your time!================";
			cout << "\n=======================================================\n";
			break;
		}
		else{
			cout << "Your response " << initializeNewSession<<" could not be matched.\n";
			cout << "Please try again!\n";
		}
	}



	////////////////////////////////////////////////////////////////////////////
	return 0;
}