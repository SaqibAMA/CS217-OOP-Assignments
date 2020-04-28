#include <iostream>
#include "Clinic.h"

using namespace std;

int main(){

	Clinic myClinic;

	myClinic.loadAppointmentsFromFile("Appointment.txt");
	myClinic.loadDoctorsFromFile("Doctor.txt");
	myClinic.loadPatientsFromFile("Patient.txt");
	myClinic.loadPatientsHistory("Patient - History.txt");
	myClinic.loadPatientsVisited("Patients visited.txt");


	/*cout << "Make the window full screen for better experience..." << endl;
	cout << "Press any key when done..." << endl;
	cin.get();

	system("cls");*/

	// myClinic.printDB();


	//// "Add a Patient"
	//char temp[100];

	//cout << "Enter Patient First Name: ";
	//cin.getline(temp, 100);

	//if (myClinic.patientExists(temp)) {
	//	
	//	cout << "A patient with that name already exists." << endl;
	//	cout << "Would you like to add one with different ID? (y/n) ";
	//	char ch;
	//	cin >> ch;

	//	if (ch == 'y') {

	//		
	//		Name pName;

	//		pName.setFirstName(temp);

	//		cout << "Enter Patient Last Name: ";
	//		cin >> temp;

	//		pName.setLastName(temp);


	//		Date pDOB;

	//		cout << "Enter Patient DOB (dd/mm/yyyy): ";
	//		cin >> pDOB;


	//		int age;

	//		cout << "Enter Patient Age: ";
	//		cin >> age;

	//		int id;

	//		cout << "Enter Patient National ID: ";
	//		cin >> id;

	//		int pId = 11;
	//		while (!myClinic.patientIDIsUnique(pId)) pId++;

	//		Patient newPatient(pId, pName, pDOB, age, id, 0);

	//		myClinic.addPatient(newPatient);

	//	}

	//}

	//myClinic.printDB();





	return 0;
}