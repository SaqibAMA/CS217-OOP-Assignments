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
	bool doctorIDIsUnique(int);
	bool tokenNumberIsUnique(int);

	bool patientExists(char*);
	bool doctorExists(char*);
	bool dateExists(Date&);


	// Options
	void printDB();
	void addPatient(Patient& P);
	void addDoctor(Doctor& D);
	void addAppointment(Appointment& A);
	void resolveAppointment(int, int, Date&);
	void printAppointmentsByDate(Date& D);
	void printAppointmentsByDoctor(int);
	void printPatientsByDoctorAndDate(int, Date&);
	void printInteractionDetails(int, int);
	void printPatientsByCommonDoctor(int);

	// Destructors
	~Clinic();
};

