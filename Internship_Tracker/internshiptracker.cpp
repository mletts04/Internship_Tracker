
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "internshiptracker.h"
using namespace std;


// Helper function to prepare value for CSV File
// Surrounds value w/ quotes and handles quotation marks
string makeCSVField(string values) {

	string result = "\"";

	for (int i = 0; i < (int)values.length(); i++) {

		if (values[i] == '"') {

			result += "\"\"";

		}

		else {

			result += values[i];

		}

	}

	result += "\"";


	return result;

}


// Helper function to separate a CSV line into fields
// Handles commas inside quotation marks
vector<string> splitCSVLine(string line) {

	vector<string> fields;
	string field = "";
	bool insideQuotes = false;

	for (int i = 0; i < (int)line.length(); i++) {

		char ch = line[i];


		if (ch == '"') {


			if (insideQuotes && i + 1 < (int)line.length() && line[i + 1] == '"') {

				field += '"';
				i++;


			}

			else {

				insideQuotes = !insideQuotes;

			}

		}

		else if (ch == ',' && !insideQuotes) {


			fields.push_back(field);
			field = "";

		}

		else {

			field += ch;

		}

	}

	fields.push_back(field);

	return fields;

}


// Default Constructor
// Initalizes an empty tracker
InternshipTracker::InternshipTracker() {

	count = 0;
	nextID = 1001;
	
}


// Add a new internship application
// Returns false if array is full
bool InternshipTracker::addApplication(string company, string position, string location, string dateApplied, string status, string deadline) {

	// Check if there is room for another application
	if (count >= MAX_APPLICAITONS) {

		return false;

	}


	// Create a new internship object
	Internship newApplication(nextID, company, position, location, dateApplied, status, deadline);

	
	// Add the object to the array
	applications[count] = newApplication;


	//Update the count and next available ID
	count++;
	nextID++;


	return true;
}


// Display all intnership applications
void InternshipTracker::displayApplications() const {

	// Check if there are any applications
	if (count == 0) {

		cout << "No Applications Found" << endl;

		return;

	}

	cout << "\nINTERNSHIP APPLICATIONS\n";
	cout << "--------------------------\n";

	// Display each application
	for (int i = 0; i < count; i++) {

		cout << applications[i].getInfo() << endl;

	}

	return;
}


// Search for an application by its ID
// Returns its array index or -1 if not found
int InternshipTracker::searchByID(int applicationID) const {

	for (int i = 0; i < count; i++) {

		if (applications[i].getApplicationID() == applicationID) {

			return i;

		}

	}


	return -1;
}


//Search for application by company
void InternshipTracker::searchByCompany(string company) const {

	bool found = false;

	for (int i = 0; i < count; i++) {


		if (applications[i].getCompany() == company) {

			cout << applications[i].getInfo() << endl;

			found = true;

		}

	}

	if (!found) {

		cout << "No applications found for " << company << "." << endl;

	}

	return;
}


// Update the status of application
// Returns false if application is not found
bool InternshipTracker::updateStatus(int applicationID, string status) {


	// Find application
	int index = searchByID(applicationID);

	// Check if the applicatione exists
	if (index == -1) {

		return false;

	}

	//Update the status
	applications[index].setStatus(status);

	return true;
}


// Sort application alphabetically by Company Name
// Uses selection sort
void InternshipTracker::sortByCompany() {

	for (int i = 0; i < count - 1; i++) {

		int minIndex = i;

		// Find alphabetically first company
		for (int j = i + 1; j < count; j++) {

			if (applications[j].getCompany() < applications[minIndex].getCompany()) {

				minIndex = j;

			}

		}

		// Swap the two internship objects
		Internship temp = applications[i];
		applications[i] = applications[minIndex];
		applications[minIndex] = temp;

	}

	return;
}


// Sort application by deadline (also selection sort)
void InternshipTracker::sortByDeadline() {

	for (int i = 0; i < count - 1; i++) {

		int minIndex = i;

		// Find the earliest dealine
		for (int j = i + 1; j < count; j++) {

			if (applications[j].getDeadline() < applications[minIndex].getDeadline()) {

				minIndex = j;

			}

		}

		// Swap the two internship objects
		Internship temp = applications[i];
		applications[i] = applications[minIndex];
		applications[minIndex] = temp;

	}

	return;
}


// Displays a summary of application statuses
void InternshipTracker::displaySummary() const {

	int interested = 0;
	int applied = 0;
	int interview = 0;
	int offer = 0;
	int rejected = 0;


	for (int i = 0; i < count; i++) {

		string status = applications[i].getStatus();

		if (status == "Interested") {

			interested++;

		}

		else if (status == "Applied") {

			applied++;

		}

		else if (status == "Interview") {

			interview++;

		}

		else if (status == "Offer") {

			offer++;

		}

		else if (status == "Rejected") {

			rejected++;

		}

	}


	// Display the summary
	cout << "\nAPPLICATION SUMMARY\n";
	cout << "----------------------\n";

	cout << "Total Applications: " << count << endl;
	cout << "Interested:         " << interested << endl;
	cout << "Applied:            " << applied << endl;
	cout << "Interview:          " << interview << endl;
	cout << "Offer:              " << offer << endl;
	cout << "Rejected:           " << rejected << endl;


	return;
}


// Save all applications to a CSV File
bool InternshipTracker::saveToFile(string filename) const {

	ofstream outFile(filename);

	// Check if File opened successfully
	if (!outFile.is_open()) {

		return false;

	}


	// Write the column headings
	outFile << "ID,Company,Position,Location," << "DateApplied,Status,Deadline\n";

	// Write each internship to the file
	for (int i = 0; i < count; i++) {

		outFile << applications[i].getApplicationID() << ","
			<< makeCSVField(applications[i].getCompany()) << ","
			<< makeCSVField(applications[i].getPosition()) << ","
			<< makeCSVField(applications[i].getLocation()) << ","
			<< makeCSVField(applications[i].getDateApplied()) << ","
			<< makeCSVField(applications[i].getStatus()) << ","
			<< makeCSVField(applications[i].getDeadline()) << "\n";

	}

	// Check whether the data was written successfully
	bool success = outFile.good();

	outFile.close();


	return success && !outFile.fail();
}


// Load applications from a CSV File
bool InternshipTracker::loadFromFile(string filename) {

	ifstream inFile(filename);


	// Check if the file opened successfully
	if (!inFile.is_open()) {

		return false;

	}

	string line;

	// Read and skip the column headings
	if (!getline(inFile, line)) {

		return false;

	}

	// Use temporary storage while reading the file
	Internship laoded[MAX_APPLICAITONS];
	int loadedCount = 0;
	int highestID = 1000;

	// Read each line of the file
	while (getline(inFile, line)) {

		// Skip empty lines
		if (line.empty()) {

			continue;

		}

		// Stop if there are too many applications
		if (loadedCount >= MAX_APPLICAITONS) {

			return false;

		}

		

		// Separate the CSV Fields
		vector<string> fields = splitCSVLine(line);

		// Each application must have seven fields
		if (fields.size() != 7) {

	
			return false;
			
		}

		// Convert the application ID to an integer
		int id;
		stringstream idStream(fields[0]);



		if (!(idStream >> id) || id <= 0) {

			return false;

		}

		// Make sure the entire ID Field is numeric
		idStream >> ws;

		if (!idStream.eof()) {

			return false;

		}

		// Check for duplication application IDs
		for (int i = 0; i < loadedCount; i++) {

			if (laoded[i].getApplicationID() == id) {

				return false;

			}


		}


		// Create the internship object
		Internship application(id, fields[1], fields[2], fields[3], fields[4], fields[5], fields[6]);

		
		// Store the application
		laoded[loadedCount] = application;
		loadedCount++;


		// Keep track of highest ID
		if (id > highestID) {

			highestID = id;

		}


	}


	// Check for file reading errors
	if (inFile.bad()) {

		return false;

	}

	inFile.close();


	// Replace existing applications w/ loaded data
	for (int i = 0; i < loadedCount; i++) {

		applications[i] = laoded[i];

	}

	count = loadedCount;

	// Cotinue assigning unique application IDs

	nextID = highestID + 1;


	return true;
}


// Return the number of stored applications
int InternshipTracker::getCount() const {

	return count;

}
