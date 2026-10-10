#pragma once

#ifndef INTERNSHIP_H
#define INTERNSHIP_H

#include <string>
using namespace std;


class Internship{

private:

	//Unqiue identifier for application
	int applicationID;

	// Info about the internship
	string company;
	string position;
	string location;

	// Application tracking info
	string dateApplied;
	string status;
	string deadline;

public:

	// Default Constructor
	Internship();


	// Constructor w/ Parameters
	Internship(int applicaitonID, string company, string position, string location, string dateApplied, string status, string deadline);


	// Getter functions
	int getApplicationID() const;
	string getCompany() const;
	string getPosition() const;
	string getLocation() const;
	string getDateApplied() const;
	string getStatus() const;
	string getDeadline() const;


	// Setter functions
	void setApplicationID(int applicationID);
	void setCompany(string company);
	void setPosition(string position);
	void setLocation(string location);
	void setDateApplied(string dateApplied);
	void setStatus(string status);
	void setdeadline(string deadline);

	// Return internship info as a string
	string getInfo() const;


};

#endif 