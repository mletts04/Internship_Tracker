
#include <iostream>
#include <string>
#include "internship.h"
using namespace std;


// Default Constructor
// Initializes an internship w/ default values
Internship::Internship(){

	applicationID = 0;
	company = "";
	position = "";
	location = "";
	dateApplied = "";
	status = "Interested";
	deadline = "";


}


// Constructor w/ Parameters
// Initializes an internship using provided values
Internship::Internship(int applicationID, string company, string position, string location, string dateApplied, string status, string deadline) {

	this->applicationID = applicationID;
	this->company = company;
	this->position = position;
	this->location = location;
	this->dateApplied = dateApplied;
	this->status = status;
	this->deadline = deadline;

}


//Getter Functions
// Return the values of the private member variables
int Internship::getApplicationID() const {

	return applicationID;

}

string Internship::getCompany() const {

	return company;

}

string Internship::getPosition() const {

	return position;

}

string Internship::getLocation() const {

	return location;

}

string Internship::getDateApplied() const {

	return dateApplied;

}

string Internship::getStatus() const {

	return status;

}

string Internship::getDeadline() const {

	return deadline;

}


// Setter functions
// Update the values of the private member variables
void Internship::setApplicationID(int applicationID) {

	this->applicationID = applicationID;
	
	return;
}


void Internship::setCompany(string company) {

	this->company = company;

	return;
}


void Internship::setPosition(string position) {

	this->position = position;

	return;
}


void Internship::setLocation(string location) {

	this->location = location;

	return;
}


void Internship::setDateApplied(string dateApplied) {

	this->dateApplied = dateApplied;

	return;
}


void Internship::setStatus(string status) {

	this->status = status;

	return;
}


void Internship::setdeadline(string deadline) {

	this->deadline = deadline;

	return;
}


//Returns internship info as a formated string
string Internship::getInfo() const {

	string result = "";

	result += "Application ID: " + to_string(applicationID) + "\n";

	result += "Comapny: " + company + "\n";

	result += "Position: " + position + "\n";

	result += "Location: " + location + "\n";

	result += "Date Applied: " + dateApplied + "\n";

	result += "Status: " + status + "\n";

	result += "Dealine: " + deadline + "\n";


	return result;
}