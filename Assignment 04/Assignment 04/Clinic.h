#pragma once

#include <iostream>
#include <fstream>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include <Windows.h>
#include <iomanip>

using namespace std;

class Clinic
{
	
private:
	
	int patientCount;
	int docCount;
	int aptCount;

	Patient* patients;
	Doctor* doctors;
	Appointment* apts;

public:
	// Constructors
	Clinic();

	// Member functions
	void loadAppointmentsFromFile(char* fileName);
	void loadDoctorsFromFile(char* fileName);
	void loadPatientsFromFile(char* fileName);
	void loadPatientsHistory(char* fileName);
	void loadPatientsVisited(char* fileName);

	void updateAppointments();

	void printAppointments();
	void printDoctors();
	void printPatients();
	void printPatientsVisited();


	void printMenu();


	// Helpers
	bool patientIDIsUnique(int);
	bool patientExists(char*);


	// Options
	void printDB();
	void addPatient(Patient& P);

	// Destructors
	~Clinic();
};

