#include <iostream>
#include "Clinic.h"

using namespace std;

extern HANDLE h;

extern void gotoxy(int x, int y);

int main(){

	Clinic myClinic;

	myClinic.loadAppointmentsFromFile("Appointment.txt");
	myClinic.loadDoctorsFromFile("Doctor.txt");
	myClinic.loadPatientsFromFile("Patient.txt");
	myClinic.loadPatientsHistory("Patient - History.txt");
	myClinic.loadPatientsVisited("Patients visited.txt");


	cout << "Make the window full screen for better experience..." << endl;
	cout << "Press enter when done..." << endl;
	cin.get();

	system("cls");

	int choice = 0;

	bool hasExit = false;

	while (!hasExit) {

		system("cls");


		cout << "+---------------------------------------------------------------+" << endl;
		cout << "+ 1.  PRINT DB                                                  +" << endl;
		cout << "+ 2.  ADD A PATIENT                                             +" << endl;
		cout << "+ 3.  ADD A DOCTOR                                              +" << endl;
		cout << "+ 4.  ADD AN APPOINTMENT                                        +" << endl;
		cout << "+ 5.  RESOLVE AN APPOINTMENT                                    +" << endl;
		cout << "+ 6.  CLEAN UP APPOINTMENTS                                     +" << endl;
		cout << "+ 7.  FILTER APPOINTMENTS BY DATE                               +" << endl;
		cout << "+ 8.  FILTER APPOINTMENTS BY DOCTOR                             +" << endl;
		cout << "+ 9.  FILTER APPOINTMENTS BY DOCTOR & DATE                      +" << endl;
		cout << "+ 10. HISTORY BETWEEN PATIENT AND DOCTOR                        +" << endl;
		cout << "+ 11. PRINT PATIENTS WHO HAVE VISITED THE SAME DOCTOR           +" << endl;
		cout << "+                                                               +" << endl;
		cout << "+                                                               +" << endl;
		cout << "+                                                               +" << endl;
		cout << "+ 12. LIST PATIENTS                                             +" << endl;
		cout << "+ 13. LIST DOCTORS                                              +" << endl;
		cout << "+ 14. LIST APPOINTMENTS                                         +" << endl;
		cout << "+                                                               +" << endl;
		cout << "+                                                               +" << endl;
		cout << "+ 0.  EXIT                                                      +" << endl;
		cout << " +---------------------------------------------------------------+" << endl;


		cout << "OPTION >> ";
		cin >> choice;

		hasExit = (choice == 0);

		if (choice == 1) {

			// Print the total DB
			myClinic.printDB();

		}
		
		else if (choice == 2) {
		
			// ADD A PATIENT

			char temp[100];

			cout << "Enter Patient First Name: ";
			cin >> temp;

			char ch = 'y';


			if (myClinic.patientExists(temp)) {

				cout << "A patient with that name already exists." << endl;
				cout << "Would you like to add one with different ID? (y/n) ";
				cin >> ch;

			}

			if (ch == 'y') {

				Name pName;

				pName.setFirstName(temp);

				cout << "Enter Patient Last Name: ";
				cin >> temp;

				pName.setLastName(temp);


				Date pDOB;

				cout << "Enter Patient DOB (dd/mm/yyyy): ";
				cin >> pDOB;


				int age;

				cout << "Enter Patient Age: ";
				cin >> age;

				int id;

				cout << "Enter Patient National ID: ";
				cin >> id;

				int pId = 1;
				while (!myClinic.patientIDIsUnique(pId)) pId++;

				Patient newPatient(pId, pName, pDOB, age, id, 0);

				myClinic.addPatient(newPatient);


			}


		}

		else if (choice == 3) {
		
		
			// ADD A DOCTOR

			char temp[100];

			cout << "Enter Doctor First Name: ";
			cin >> temp;

			char ch = 'y';


			if (myClinic.doctorExists(temp)) {

				cout << "A doctor with that name already exists." << endl;
				cout << "Would you like to add one with different ID? (y/n) ";
				cin >> ch;

			}



			if (ch == 'y') {

				Name pName;

				pName.setFirstName(temp);

				cout << "Enter Doctor Last Name: ";
				cin >> temp;

				pName.setLastName(temp);


				Date pDOB;

				cout << "Enter Doctor DOB (dd/mm/yyyy): ";
				cin >> pDOB;


				int age;

				cout << "Enter Doctor Age: ";
				cin >> age;

				int id;

				cout << "Enter Doctor National ID: ";
				cin >> id;

				char specialization[100];

				cout << "Enter Doctor Specialization: ";
				cin >> specialization;

				int dId = 1;
				while (!myClinic.doctorIDIsUnique(dId)) dId++;

				Doctor newDoctor(dId, pName, pDOB, age, id, specialization);

				myClinic.addDoctor(newDoctor);


			}
		
		
		
		}


		else if (choice == 4) {
		
			// MAKE AN APPOINTMENT

			char ch;

			cout << "Enter a new patient? (y / n) ";
			cin >> ch;

			int pId = -1, dId = -1;


			if (ch == 'y') {
	

				char temp[100];

				cout << "Enter Patient First Name: ";
				cin >> temp;

				ch = 'y';


				if (myClinic.patientExists(temp)) {

					cout << "A patient with that name already exists." << endl;
					cout << "Would you like to add one with different ID? (y/n) ";
					cin >> ch;

				}

				if (ch == 'y') {

					Name pName;

					pName.setFirstName(temp);

					cout << "Enter Patient Last Name: ";
					cin >> temp;

					pName.setLastName(temp);


					Date pDOB;

					cout << "Enter Patient DOB (dd/mm/yyyy): ";
					cin >> pDOB;


					int age;

					cout << "Enter Patient Age: ";
					cin >> age;

					int id;

					cout << "Enter Patient National ID: ";
					cin >> id;

					pId = 1;
					while (!myClinic.patientIDIsUnique(pId)) pId++;

					Patient newPatient(pId, pName, pDOB, age, id, 0);

					myClinic.addPatient(newPatient);


				}


			}

			char diseaseType[100];
			int fee;

			while (myClinic.patientIDIsUnique(pId)) {
				cout << "Enter existing patient ID: ";
				cin >> pId;

				if (myClinic.patientIDIsUnique(pId)) cout << "Patient does not exist. Enter again!" << endl;

			}

			while (myClinic.doctorIDIsUnique(dId)) {
				cout << "Enter existing doctor ID: ";
				cin >> dId;

				if (myClinic.doctorIDIsUnique(dId)) cout << "Doctor does not exist. Enter again!" << endl;

			}

			Date aptDate;

			cout << "Enter appointment date: ";
			cin >> aptDate;

			mTime aptTime;

			cout << "Enter appointment time: ";
			cin >> aptTime;

			cout << "Enter disease type: ";
			cin >> diseaseType;

			cout << "Enter fee: ";
			cin >> fee;

			int tokenNum = 1;
			while(!myClinic.tokenNumberIsUnique(tokenNum)) tokenNum++;

			Appointment newApt(diseaseType, pId, dId, aptDate, aptTime, tokenNum, fee, false);

			myClinic.addAppointment(newApt);

		
		
		}

		else if (choice == 5) {
		
			// RESOLVE AN APPOINTMENT

			int pId = -1, dId = -1;

			while (myClinic.patientIDIsUnique(pId)) {
				cout << "Enter existing patient ID: ";
				cin >> pId;

				if (myClinic.patientIDIsUnique(pId)) cout << "Patient does not exist. Enter again!" << endl;

			}

			while (myClinic.doctorIDIsUnique(dId)) {
				cout << "Enter existing doctor ID: ";
				cin >> dId;

				if (myClinic.doctorIDIsUnique(dId)) cout << "Doctor does not exist. Enter again!" << endl;

			}


			Date aptDate;

			while (!myClinic.dateExists(aptDate)) {
		
				cout << "Enter existing appointment date: ";
				cin >> aptDate;

			}

			myClinic.resolveAppointment(dId, pId, aptDate);


		
		}

		else if (choice == 6) {
			
			myClinic.updateAppointments();
			cout << "Appointments Updated!" << endl;

		}

		else if (choice == 7) {
			
			// PRINT APPOINTMENTS BY DATE

			Date query;
			cout << "Enter date to filter appointments: ";
			cin >> query;

			if (myClinic.dateExists(query)) {
	
				myClinic.printAppointmentsByDate(query);

			} else {
		
				cout << "No pending appointments on this date." << endl;

			}

		}


		else if (choice == 8) {
			

			// DETAILS OF APPOINTMENTS FOR A DOCTOR

			int dId = -1;

			while (myClinic.doctorIDIsUnique(dId)) {
				cout << "Enter existing doctor ID: ";
				cin >> dId;

				if (myClinic.doctorIDIsUnique(dId)) cout << "Doctor does not exist. Enter again!" << endl;

			}

			myClinic.printAppointmentsByDoctor(dId);


		}


		else if (choice == 9) {
			

			// FILTER PATIENTS BY DOCTOR AND DATE
			int dId = -1;

			while (myClinic.doctorIDIsUnique(dId)) {
				cout << "Enter existing doctor ID: ";
				cin >> dId;

				if (myClinic.doctorIDIsUnique(dId)) cout << "Doctor does not exist. Enter again!" << endl;

			}

			Date filterDate;

			cout << "Enter filter date: ";
			cin >> filterDate;


			myClinic.printPatientsByDoctorAndDate(dId, filterDate);



		}

		else if (choice == 10) {
		
			
			// COMPLETE INTERACTION DETAILS

			int dId = -1, pId = -1;

			while (myClinic.patientIDIsUnique(pId)) {
				cout << "Enter existing patient ID: ";
				cin >> pId;

				if (myClinic.patientIDIsUnique(pId)) cout << "Patient does not exist. Enter again!" << endl;

			}

			while (myClinic.doctorIDIsUnique(dId)) {
				cout << "Enter existing doctor ID: ";
				cin >> dId;

				if (myClinic.doctorIDIsUnique(dId)) cout << "Doctor does not exist. Enter again!" << endl;

			}

			myClinic.printInteractionDetails(dId, pId);


		}

		else if (choice == 11) {
		


			// PRINT PATIENTS BY COMMON DOCTOR
			int dId = -1;


			while (myClinic.doctorIDIsUnique(dId)) {
				cout << "Enter existing doctor ID: ";
				cin >> dId;

				if (myClinic.doctorIDIsUnique(dId)) cout << "Doctor does not exist. Enter again!" << endl;

			}

			myClinic.printPatientsByCommonDoctor(dId);
		
		
		}

		else if (choice == 12) {
			
			myClinic.printPatients();

		}

		else if (choice == 13) {
			
			myClinic.printDoctors();

		}

		else if (choice == 14) {
			
			cout << "\n\n";
			myClinic.printAppointments();
			cout << "\n\n";

		}

		cin.get();
		cout << "Press enter..." << endl;
		cin.get();

	}





	return 0;
}