
#include <iostream>
#include <string>
#include <sstream>
#include "internshiptracker.h"
using namespace std;


int main() {

	// Creates an internship tracker object
	InternshipTracker tracker;

	// Variables for menu and user input
	int choice = 0;
	int applicationID;

	string company;
	string position;
	string location;
	string dateApplied;
	string status;
	string deadline;

	string input;
	string filename = "internships.csv";


	// Load previously saved applicaitons IF available
	if (tracker.loadFromFile(filename)) {

		cout << "Applications loaded successfully.\n";

	}

	else {

		cout << "No saved applications loaded.\n";

	}

	// Continue displaying menu until the user exits
	do {


		cout << "\n-------------------------------------\n";
		cout << "   INTERNSHIP APPLICATION TRACKER   \n";
		cout << "-------------------------------------\n";

		cout << "1. View All Applications\n";
		cout << "2. Add New Application\n";
		cout << "3. Search Application\n";
		cout << "4. Update Application Status\n";
		cout << "5. Sort Applications\n";
		cout << "6. View Application Summary\n";
		cout << "7. Save Applications\n";
		cout << "8. Exit\n";


		cout << "\nEnter your choice:\t";
		getline(cin, input);


		// Convert the menu input an integer
		stringstream menuStream(input);

		if (!(menuStream >> choice)) {

			choice = 0;

		}

		else {

			//Reject extra characters after the number
			menuStream >> ws;

			if (!menuStream.eof()) {

				choice = 0;

			}

		}


		// Perform the selected menu operation
		switch (choice) {

		case 1: 

			// Display all internship applications
			tracker.displayApplications();
			break;
		

		case 2: 

			// Add a new internship applicaiton
			cout << "\nADD NEW APPLICATION\n";
			cout << "----------------------\n";

			cout << "Company: ";
			getline(cin, company);

			cout << "Position: ";
			getline(cin, position);

			cout << "Location: ";
			getline(cin, location);

			cout << "Date Applied (YYYY-MM-DD): ";
			getline(cin, dateApplied);

			cout << "Status (Interested, Applied, Interview, Offer, Rejected): ";
			getline(cin, status);

			cout << "Deadline (YYYY-MM-DD): ";
			getline(cin, deadline);


			// Add the application to the tracker
			if (tracker.addApplication(company, position, location, dateApplied, status, deadline)) {

				cout << "\nApplication added successfully!\n";

			}

			else {

				cout << "\nUnable to add application. The Tracker is full!!\n";

			}
		
			break;


		case 3: {

			// Search for an application by ID or company
			int searchChoice = 0;
			
			cout << "\nSEARCH APPLICATIONS\n";
			cout << "---------------------\n";
			cout << "1. Search by Application ID\n";
			cout << "2. Search by Company Name\n";


			cout << "\nEnter your choice: ";
			getline(cin, input);

			stringstream searchStream(input);

			if (!(searchStream >> searchChoice)) {

				searchChoice = 0;

			}

			else {

				searchStream >> ws;

				if (!searchStream.eof()) {

					searchChoice = 0;

				}

			}

			if (searchChoice == 1) {

				cout << "Enter Application ID: ";
				getline(cin, input);

				stringstream idStream(input);


				// Check that the ID is a valid integer
				if (!(idStream >> applicationID)) {

					cout << "Invalid application ID.\n";
					break;

				}

				idStream >> ws;

				if (!idStream.eof()) {

					cout << "Invalid application ID.\n";
					break;

				}

				// Find the applicaiton in the array
				int index = tracker.searchByID(applicationID);


				if (index == -1) {

					cout << "Application not found.\n";

				}

				else {

					cout << "Application found at array index " << index << ".\n";

					//Display all records so the matching application can be identified by ID
					tracker.displayApplications();

				}
			}

			else if(searchChoice == 2){

				cout << "Enter Company Name: ";
				getline(cin, company);

				tracker.searchByCompany(company);

			}

			else {

				cout << "Invalid search option.\n";

			}

			break;


		}

		case 4: {

			// Update an existing application's status
			cout << "\nUPDATE APPLICATION STATUS\n";
			cout << "----------------------------\n";

			cout << "Enter Application ID: ";
			getline(cin, input);

			stringstream idStream(input);

			if (!(idStream >> applicationID)) {

				cout << "Invalid application ID.\n";
				break;

			}

			idStream >> ws;

			if (!idStream.eof()) {

				cout << "Invalid application ID.\n";
				break;

			}

			cout << "Enter New Status (Interested, Applied, Interview, Offer, Rejected): ";
			getline(cin, status);


			// Attempt to update the application
			if (tracker.updateStatus(applicationID, status)) {

				cout << "Application status updated.\n";

			}

			else {

				cout << "Application not found!!\n";

			}

			break;
		}

		case 5: {

			// Sort internship applications
			int sortChoice = 0;

			cout << "\nSORT APPLCIATIONS\n";
			cout << "--------------------\n";
			cout << "1. Sort by Company Name\n";
			cout << "2. Sort by Deadline\n";

			cout << "\nEnter your choice: ";
			getline(cin, input);


			stringstream sortStream(input);

			if (!(sortStream >> sortChoice)) {

				sortChoice = 0;

			}

			else {

				sortStream >> ws;

				if (!sortStream.eof()) {

					sortChoice = 0;

				}

			}

			if (sortChoice == 1) {

				tracker.sortByCompany();

				cout << "\nSorted by company name.\n";
				tracker.displayApplications();

			}

			else if (sortChoice == 2) {

				tracker.sortByDeadline();

				cout << "\nSorted by deadline.\n";
				tracker.displayApplications();

			}

			else {

				cout << "Invalid sort option.\n";

			}

			break;

		}


		case 6:

			// Display a summary of application statuses
			tracker.displaySummary();
			break;


		case 7:
			
			// Save all internship applications to a file
			if (tracker.saveToFile(filename)) {

				cout << "Application saved successfully.\n";

			}

			else {

				cout << "Error saving applications.\n";

			}
			break;


		case 8:

			// Save applications before exiting
			cout << "\nSaving applications...\n";


			if (tracker.saveToFile(filename)) {

				cout << "Applications saved successfully.\n";
				cout << "Goodbye! Have a good day!\n";

			}

			else {
				
				cout << "Error saving applications.\n";
				cout << "Changes may not have been saved!\n";

			}
			break;

			
		default:
			cout << "Invalid choice! Please try again.\n";
			break;

		}


	} while (choice != 8);


	return 0;
}