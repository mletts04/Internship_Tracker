#pragma once

#ifndef INTERNSHIPTRACKER_H
#define INTERNSHIPTRACKER_H

#include <string>
#include "internship.h"
using namespace std;

class InternshipTracker {

private:

	// Max number of internship applciations
	static const int MAX_APPLICAITONS = 100;

	// Array to store internship applications
	Internship applications[MAX_APPLICAITONS];

	// Number of applications currently stored
	int count;

	// ID to assign to next application
	int nextID;

public:

	// Default Constructor
	InternshipTracker();

	// Add a new internship application
	bool addApplication(string company, string position, string location, string dateApplied, string status, string deadline);
	
	// Display all intnership applications
	void displayApplications() const;

	// Search for an application by its ID
	int searchByID(int applicationID) const;

	//Search for application by company
	void searchByCompany(string company) const;

	// Update the status of application
	bool updateStatus(int applicationID, string status);

	// Sort application by Company Name
	void sortByCompany();

	// Sort application by deadline
	void sortByDeadline();

	// Display application statistics
	void displaySummary() const;

	// Save applications to a CSV File
	bool saveToFile(string filename) const;

	// Load applications from a CSV File
	bool loadFromFile(string filename);

	// Return the number of applications
	int getCount() const;

};

#endif 