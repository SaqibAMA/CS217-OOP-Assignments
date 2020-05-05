#include "Clinic.h"

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y) {

    COORD scrn;

    scrn.X = x, scrn.Y = y;

    SetConsoleCursorPosition(h,scrn);

}

Clinic::Clinic() {

	patients = nullptr;
	doctors = nullptr;
	apts = nullptr;

	patientCount = 0;
	docCount = 0;
	aptCount = 0;

}

void Clinic::loadAppointmentsFromFile(char* fileName) {
	
	if (apts != nullptr) delete[] apts;

	ifstream fin;
	fin.open(fileName);

	char buff[200];

	// finds out how many
	// records are there
	// in the file

	int totalRecord = 0;

	while (!fin.eof()) {
		fin.getline(buff, 200);
		totalRecord++;
	}

	fin.clear();
	fin.seekg(0, ios::beg);

	if (totalRecord > 0)
		apts = new Appointment[totalRecord];


	// DiseaseType, pid, did, day, month, year, hour, min, sec, token, fee, status

	for (int i = 0; i < totalRecord; i++) {
		
		fin >> buff;
		apts[i].setDiseaseType(buff);
		fin >> buff;
		apts[i].setPiD(atoi(buff));
		fin >> buff;
		apts[i].setDiD(atoi(buff));

		// buffer to read date month and time
		{
			int d, m, y;

			fin >> d;
			fin >> m;
			fin >> y;

			// making it into an object
			Date aptDate(d, m, y);

			apts[i].setAppDate(aptDate);
		
		}
		
		{
			int h, m, s;

			fin >> h;
			fin >> m;
			fin >> s;

			mTime aptTime(h, m, s);

			apts[i].setAppTime(aptTime);
		}

		fin >> buff;
		apts[i].setTokenNumber(atoi(buff));

		fin >> buff;
		apts[i].setFee(atof(buff));

		fin >> buff;

		apts[i].setStatus(bool(atoi(buff)));

		fin.ignore();

	}

	aptCount = totalRecord;

	fin.close();

}

void Clinic::loadDoctorsFromFile(char* fileName) {

	ifstream fin;
	fin.open(fileName);

	char buff[100];

	int totalRecord = 0;
	while (!fin.eof()) {
		fin.getline(buff, 100);
		totalRecord++;
	}

	fin.clear();
	fin.seekg(0, ios::beg);

	if (totalRecord > 0)
		doctors = new Doctor[totalRecord];

	// DID, fname, lname, day, month, year, Age, Nid, specialization

	for (int i = 0; i < totalRecord; i++) {
	
		fin >> buff;
		doctors[i].setDId(atoi(buff));

		Name docName;
		fin >> buff;
		docName.setFirstName(buff);
		fin >> buff;
		docName.setLastName(buff);

		doctors[i].Person::setPName(docName);

		Date docDOB;

		fin >> buff;
		docDOB.setDay(atoi(buff));
		fin >> buff;
		docDOB.setMonth(atoi(buff));
		fin >> buff;
		docDOB.setYear(atoi(buff));

		doctors[i].Person::setDOB(docDOB);

		fin >> buff;

		doctors[i].Person::setAge(atoi(buff));

		fin >> buff;

		doctors[i].Person::setID(atoi(buff));

		fin >> buff;

		doctors[i].setSpecialization(buff);
	
	}

	docCount = totalRecord;

	fin.close();

}

void Clinic::loadPatientsFromFile(char* fileName) {

	ifstream fin;
	fin.open(fileName);

	char buff[100];

	int totalRecord = 0;
	while (!fin.eof()) {
		
		fin.getline(buff, 100);
		totalRecord++;

	}

	fin.clear();
	fin.seekg(0, ios::beg);

	if (totalRecord > 0)
		patients = new Patient[totalRecord];

	// PID, fname, lname, day, month, year, Age, Nid, History

	for (int i = 0; i < totalRecord; i++) {
	
		fin >> buff;
		patients[i].setPId(atoi(buff));

		fin >> buff;
		Name personName;
		personName.setFirstName(buff);
		fin >> buff;
		personName.setLastName(buff);
		patients[i].setPName(personName);

		int d, m, y;

		fin >> d;
		fin >> m;
		fin >> y;

		Date DOB(d, m, y);

		patients[i].setDOB(DOB);

		fin >> buff;
		patients[i].setAge(atoi(buff));

		fin >> buff;
		patients[i].setID(atoi(buff));

		fin >> buff;
		patients[i].setHasHistory((bool)atoi(buff));

	}

	patientCount = totalRecord;

	fin.close();

}

void Clinic::loadPatientsHistory(char* fileName) {
	
	ifstream fin;
	fin.open(fileName);

	char buff[200];

	while (!fin.eof()) {

		fin >> buff;

		int pId = atoi(buff);
		int pInd = 0;

		for (int i = 0; i < patientCount; i++) {
			
			if (patients[i].getPId() == pId) pInd = i;

		}

		//fin.getline(buff, 200);
		bool endOfLine = false;

		// PID, Disease type, day, month, year, hor, min, sec, DID, Fee

		while (!endOfLine) {
			
			pRecord tempRecord;

			fin >> buff;
			tempRecord.setDiseaseType(buff);

			{

				int d, m, y;

				fin >> d;
				fin >> m;
				fin >> y;

				Date tempDate(d, m, y);

				tempRecord.setVisDate(tempDate);

			}

			{
			
				int h, m, s;

				fin >> h;
				fin >> m;
				fin >> s;

				mTime tempTime(h, m, s);

				tempRecord.setVisTime(tempTime);

			}

			fin >> buff;
			tempRecord.setAssignedDoc(atoi(buff));

			fin >> buff;
			tempRecord.setFeePaid((float) atof(buff));

			char ch = fin.get();
			endOfLine = (ch == '\n' || fin.eof());

			patients[pInd].addRecord(tempRecord.getDiseaseType(),
				tempRecord.getVisDate(),
				tempRecord.getVisTime(),
				tempRecord.getAssignedDoc(),
				tempRecord.getFeePaid());


		}


	}


	fin.close();

}

void Clinic::loadPatientsVisited(char* fileName) {

	ifstream fin;
	fin.open(fileName);

	while (!fin.eof()) {
	
		int* buff = new int[50];
		int buffSize = 0;

		int docId;
		int docInd;

		fin >> docId;

		for (int i = 0; i < docCount; i++) {
			
			if (doctors[i].getDId() == docId) docInd = i;

		}

		bool endOfLine = false;

		while (!endOfLine && !fin.eof()) {
			

			fin >> buff[buffSize++];

			char ch = fin.get();
			
			endOfLine = (ch == '\n');

		}

		if (buff[0] != 0) {
			doctors[docInd].setPatientsVisited(buff, buffSize);
		}

	}

	fin.close();

	// implement this function
	// then move on to building the menu

}

void Clinic::updateAppointments() {

	bool arrayModified = false;

	for (int i = 0; i < aptCount; i++) {
		
		if (apts[i].getStatus() != 0) {

			arrayModified = true;

			for (int j = i; j < aptCount - 1; j++) {
			
				apts[j] = apts[j + 1];
			
			}

			aptCount--;

		}

	}

	if (arrayModified && aptCount > 0) {
		
		Appointment* _apts = new Appointment[aptCount];

		for (int i = 0; i < aptCount; i++) {
		
			_apts[i] = apts[i];

		}

		if (apts != nullptr) delete[] apts;
		apts = _apts;

	} else if (aptCount == 0) {
		
		apts = nullptr;

	}

}

void Clinic::printAppointments() {

	for (int i = 0; i < aptCount; i++) {

		cout
			<< "NO: " << i + 1 << " "
			<< "DID: " << apts[i].getDiD() << " "
			<< "PID: " << apts[i].getPiD() << "   "
			<< "Date: "<< apts[i].getAppDate() << " "
			<< "Time: " << apts[i].getAppTime() << "   "
			<< "Disease: " << apts[i].getDiseaseType() << "   "
			<< "Token: " << apts[i].getTokenNumber() << " "
			<< "Fee: " << apts[i].getFee() << " "
			<< "Status: " << apts[i].getStatus() << endl;

	}

}

void Clinic::printDoctors() {
	
	for (int i = 0; i < docCount; i++) {
		

		cout
			<< "Name: " << doctors[i].getPName() << " "
			<< "Age: " << doctors[i].getAge() << " "
			<< "DOB: " << doctors[i].getDOB() << " "
			<< "ID: " << doctors[i].getID() << "   "
			<< "DID: " << doctors[i].getDId() << " "
			<< "Spec.: " << doctors[i].getSpecialization() << " " << endl
			<< "P. Visited: ";
		
		int* pVis = doctors[i].getPatientsVisited();
		int pVisSize = doctors[i].getPatientsVisitedSize();

		for (int j = 0; j < pVisSize && pVis != nullptr; j++) cout << pVis[j] << " ";
		
		cout << "\n\n";

	}

}

void Clinic::printPatients() {
	
	for (int i = 0; i < patientCount; i++) {
		
		cout
			<< "\n\nName: " << patients[i].getPName() << " "
			<< "Age: " << patients[i].getAge() << " "
			<< "DOB: " << patients[i].getDOB() << " "
			<< "ID: " << patients[i].getID() << " "
			<< "PID: " << patients[i].getPId() << " "
			<< "\n\nHistory: ";

		if (patients[i].getHasHistory()) {

			pRecord** history = patients[i].getHistory();
			int historySize = patients[i].getHistorySize();

			for (int i = 0; i < historySize; i++) {
				
				cout << endl 
				<< "\nDID: " << history[i][0].getAssignedDoc() << " "
				<< "Disease Type" << history[i][0].getDiseaseType() << " "
				<< "Vis. Date: " << history[i][0].getVisDate() << " "
				<< "Vis. Time: " << history[i][0].getVisTime() << endl;

			}
		
		}
		else {
			
			cout << "None." << endl;

		}

		cout << endl << endl;

	}

}

void Clinic::printPatientsVisited() {
	
	for (int i = 0; i < docCount; i++) {
		
		int* list = doctors[i].getPatientsVisited();
		int listSize = doctors[i].getPatientsVisitedSize();

		cout << "ID -> " << doctors[i].getDId() << " -> ";

		for (int j = 0; j < listSize && list != nullptr; j++) {
			
			cout << list[j] << " ";

		}

		cout << endl;

	}

}


bool Clinic::patientExists(char* name) {
	
	for (int i = 0; i < patientCount; i++) {
		
		if (strcmp(name, patients[i].getPName().getFirstName()) == 0) return true;

	}

	return false;

}

bool Clinic::patientIDIsUnique(int n) {

	for (int i = 0; i < patientCount; i++) {

		if (n == patients[i].getPId()) {
			return false;
		}

	}

	return true;

}

bool Clinic::doctorExists(char* name) {
	
	for (int i = 0; i < docCount; i++) {
		
		if (strcmp(name, doctors[i].getPName().getFirstName()) == 0) return true;

	}

	return false;

}

bool Clinic::doctorIDIsUnique(int n) {
	
	for (int i = 0; i < docCount; i++) {
		
		if (n == doctors[i].getDId()) return false;

	}

	return true;

}

bool Clinic::tokenNumberIsUnique(int n) {
	
	for (int i = 0; i < aptCount; i++) {
		
		if (n == apts[i].getTokenNumber()) return false;

	}

	return true;

}

void Clinic::printMenu() {

	int xOff = 0, yOff = 0;

	SetConsoleTextAttribute(h, 11);

	gotoxy(10 + xOff, 3 + yOff);
	cout << "1. Print DB" << endl;
	gotoxy(10 + xOff, 4 + yOff);
	cout << "2. Add a patient" << endl;
	gotoxy(10 + xOff, 5 + yOff);
	cout << "3. Add a doctor" << endl;
	gotoxy(10 + xOff, 6 + yOff);
	cout << "4. Make an appoinment" << endl;
	gotoxy(10 + xOff, 7 + yOff);
	cout << "5. Update appointment list" << endl;
	gotoxy(10 + xOff, 8 + yOff);
	cout << "6. Update patient data" << endl;
	gotoxy(10 + xOff, 9 + yOff);
	cout << "7. Update doctor data" << endl;
	gotoxy(10 + xOff, 10 + yOff);
	cout << "8. See patient visits on a specific day" << endl;
	

}

bool Clinic::dateExists(Date& D) {
	
	for (int i = 0; i < aptCount; i++) {

		if (apts[i].getAppDate().getDay() == D.getDay() &&
			apts[i].getAppDate().getMonth() == D.getMonth() &&
			apts[i].getAppDate().getYear() == D.getYear()) return true;

	}

	return false;

}

// Options

void Clinic::printDB() {

	system("cls");

	gotoxy(10, 2);
	cout << "+ -- DOCTORS -- +\n";

	for (int i = 0, yDev = 0; i < docCount; i++, yDev += 3) {
	
		gotoxy(10, 5 + yDev);
		cout << doctors[i].getDId() << setw(3) << " ";
		cout << doctors[i].getPName() << setw(2) << " ";
		cout << doctors[i].getSpecialization();

	}

	cout << endl;

	gotoxy(58, 2);
	cout << "+ -- PATIENTS -- +\n";

	for (int i = 0, yDev = 0; i < patientCount; i++, yDev += 3) {
	
		gotoxy(58, 5 + yDev);
		cout << patients[i].getPId() << setw(3) << " ";
		cout << patients[i].getPName() << setw(2) << " ";
		(patients[i].getHasHistory()) ? cout << "History Available." : cout << "No History.";

	}

	cout << endl;

	gotoxy(118, 2);
	cout << "+ -- APPOINTMENTS -- +\n";

	for (int i = 0, yDev = 0; i < aptCount; i++, yDev += 3) {
	
		gotoxy(118, 5 + yDev);
		cout << apts[i].getAppDate() << "\t\t";
		cout << apts[i].getAppTime() << " ";
		cout << " DID: " << apts[i].getDiD() << " PID: " << apts[i].getPiD() << " ";
		(apts[i].getStatus()) ? cout << "Completed." : cout << "Pending.";

	}


	cout << endl;


}

void Clinic::addPatient(Patient& P) {
	
	Patient* _patients = new Patient[patientCount + 1];

	for (int i = 0; i < patientCount; i++) {
		
		_patients[i] = patients[i];

	}

	_patients[patientCount++] = P;

	if (patients != nullptr) delete[] patients;

	patients = _patients;

}

void Clinic::addDoctor(Doctor& D) {
	
	Doctor* _doctors = new Doctor[docCount + 1];

	for (int i = 0; i < docCount; i++) {
		
		_doctors[i] = doctors[i];

	}

	_doctors[docCount++] = D;

	if (doctors != nullptr) delete[] doctors;

	doctors = _doctors;

}

void Clinic::addAppointment(Appointment& A) {

	int patientInd = 0;

	for (int i = 0; i < patientCount; i++) {
		
		if (patients[i].getPId() == A.getPiD()) {
			
			patientInd = i;

		}

	}

	int docInd = 0;

	for (int i = 0; i < docCount; i++) {
		
		if (doctors[i].getDId() == A.getDiD()) {
			
			docInd = i;

		}

	}

	bool aptValid = false;

	if (patients[patientInd].getAge() <= 12
		&& strcmp(doctors[docInd].getSpecialization(), "Child_Specialist") != 0) {


		bool childSpecialistExists = false;
		int childSpecialistInd = 0;

		for (int i = 0; i < docCount && ! childSpecialistExists; i++) {
			
			childSpecialistExists = 
				(strcmp(doctors[i].getSpecialization(), "Child_Specialist") == 0);
			childSpecialistInd = i;

		}

		if (childSpecialistExists) {
		
			A.setDiD(doctors[childSpecialistInd].getDId());

			cout << "Child Specialist assigned because the patient was 12 years old! " << endl;

			aptValid = true;


		}


	}
	else {
	
		aptValid = true;

	}

	if (aptValid) {
		
		Appointment* _apts = new Appointment[aptCount + 1];

		for (int i = 0; i < aptCount; i++) {

			_apts[i] = apts[i];

		}

		_apts[aptCount++] = A;

		if (apts != nullptr) delete[] apts;

		apts = _apts;

	}
	else {

		cout << "Appointment failed!" << endl <<
			"The patient is less than 12 years old and we don't have a Child Specialist!"
			<< endl;

	}

}

void Clinic::resolveAppointment(int dId, int pId, Date& D) {

	for (int i = 0; i < aptCount; i++) {


		/*cout << "Conditions->" << endl;
		cout << apts[i].getDiD() << dId << (apts[i].getDiD() == dId) << endl;
*/
		
		if (
			apts[i].getDiD() == dId &&
			apts[i].getPiD() == pId &&
			apts[i].getAppDate().getDay() == D.getDay() &&
			apts[i].getAppDate().getMonth() == D.getMonth() &&
			apts[i].getAppDate().getYear() == D.getYear() &&
			apts[i].getStatus() == false
			) {
		
				int docInd, pInd;

				
				apts[i].setStatus(true);
				
				for (int j = 0; j < docCount; j++) {
					
					if (doctors[j].getDId() == dId) docInd = j;

				}
				
				for (int j = 0; j < patientCount; j++) {
					
					if (patients[j].getPId() == pId) pInd = j;

				}

				doctors[docInd].addPatientVisited(pId);
				patients[pInd].addRecord(apts[i].getDiseaseType(), apts[i].getAppDate(), apts[i].getAppTime(), dId, apts[i].getFee());
		}

	}

}

void Clinic::printAppointmentsByDate(Date& D) {
	
	for (int i = 0; i < aptCount; i++) {
		
		if (
			apts[i].getAppDate().getDay() == D.getDay() &&
			apts[i].getAppDate().getMonth() == D.getMonth() &&
			apts[i].getAppDate().getYear() == D.getYear() &&
			apts[i].getStatus() == 0) {
			
				cout << apts[i] << endl;

		}

	}

}

void Clinic::printAppointmentsByDoctor(int dId) {

	bool found = false;

	for (int i = 0; i < aptCount; i++) {
		
		if (apts[i].getDiD() == dId && apts[i].getStatus() == 0) {
			
			found = true;
			cout << apts[i] << endl;

		}

	}

	if (!found) cout << "No appointments found!" << endl;

}

void Clinic::printPatientsByDoctorAndDate(int dId, Date& D) {
	
	bool historyFound = false;

	for (int i = 0; i < patientCount; i++) {
		
		pRecord** history = patients[i].getHistory();
		int historySize = patients[i].getHistorySize();

		if (history != nullptr && historySize > 0) {
		
			for (int j = 0; j < historySize; j++) {
				
				if (
					history[j][0].getAssignedDoc() == dId &&
					history[j][0].getVisDate().getDay() == D.getDay() &&
					history[j][0].getVisDate().getMonth() == D.getMonth() &&
					history[j][0].getVisDate().getYear() == D.getYear()
					) {
					
						historyFound = true;

						cout << "\nDoctor ID: " << dId << " visited, " << patients[i].getPName() << " on " << history[j][0].getVisDate() << endl;
						cout << "\nPatient Details-> \n" << endl;
						cout << patients[i] << endl; 

				}

			}
		
		}

	}

	if (!historyFound) cout << "No patients found! " << endl;

}

void Clinic::printInteractionDetails(int dId, int pId) {
	
	bool historyFound = false;

	for (int i = 0; i < patientCount; i++) {
		
		if (patients[i].getPId() == pId) {		
		
				pRecord** history = patients[i].getHistory();
				int historySize = patients[i].getHistorySize();

				if (history != nullptr && historySize > 0) {
		
					for (int j = 0; j < historySize; j++) {
				
						if (history[j][0].getAssignedDoc() == dId) {
					
								historyFound = true;

								cout << "\nDoctor ID: " << dId << " visited, " << patients[i].getPName() << " on " << history[j][0].getVisDate() << endl;

						}

					}
		
				}
		
		}

	}

	if (!historyFound) cout << "No history found! " << endl;


}

void Clinic::printPatientsByCommonDoctor(int dId) {

	cout << "Doctor details-> " << endl;

	for (int i = 0; i < docCount; i++) {
		
		if (doctors[i].getDId() == dId) {
			
			cout << doctors[i] << endl;

		}

	}


	bool historyFound = false;

	for (int i = 0; i < patientCount; i++) {
		
		pRecord** history = patients[i].getHistory();
		int historySize = patients[i].getHistorySize();

		if (history != nullptr) {
			
			
			for (int j = 0; j < historySize; j++) {
				
				if (history[j][0].getAssignedDoc() == dId) {

					historyFound = true;
					
					cout << "\nDoctor ID: " << dId << " visited, " << patients[i].getPName() << " on " << history[j][0].getVisDate() << endl;
					cout << "\nPatient Details-> \n" << endl;
					cout << patients[i] << endl;

				}

			}


		}

	}

	if (!historyFound) cout << "No such patients found!" << endl;

}

void Clinic::saveData(char* aptFile,
	char* docFile,
	char* pFile,
	char* pHistoryFile,
	char* pVisitedFile) {
	

	// Saving Appointments

	ofstream fout;
	fout.open(aptFile);


	for (int i = 0; i < aptCount; i++) {

		fout << apts[i].getDiseaseType() << " "
			<< apts[i].getPiD() << " "
			<< apts[i].getDiD() << " "
			<< apts[i].getAppDate().getDay() << " "
			<< apts[i].getAppDate().getMonth() << " "
			<< apts[i].getAppDate().getYear() << " "
			<< apts[i].getAppTime().getHour() << " "
			<< apts[i].getAppTime().getMin() << " "
			<< apts[i].getAppTime().getSec() << " "
			<< apts[i].getTokenNumber() << " "
			<< apts[i].getFee() << " "
			<< apts[i].getStatus();

		if (i < aptCount - 1) fout << endl;

	}


	fout.close();


	// Saving Doctors

	fout.open(docFile);


	for (int i = 0; i < docCount; i++) {
		
		fout
			<< doctors[i].getDId() << " "
			<< doctors[i].getPName().getFirstName() << " "
			<< doctors[i].getPName().getLastName() << " "
			<< doctors[i].getDOB().getDay() << " "
			<< doctors[i].getDOB().getMonth() << " "
			<< doctors[i].getDOB().getYear() << " "
			<< doctors[i].getAge() << " "
			<< doctors[i].getID() << " "
			<< doctors[i].getSpecialization();

		if (i < docCount - 1) fout << endl;

	}


	fout.close();

	
	// Saving patients

	fout.open(pFile);


	for (int i = 0; i < patientCount; i++) {
		
		fout
			<< patients[i].getPId() << " "
			<< patients[i].getPName().getFirstName() << " "
			<< patients[i].getPName().getLastName() << " "
			<< patients[i].getDOB().getDay() << " "
			<< patients[i].getDOB().getMonth() << " "
			<< patients[i].getDOB().getYear() << " "
			<< patients[i].getAge() << " "
			<< patients[i].getID() << " "
			<< patients[i].getHasHistory();

		if (i < patientCount - 1) fout << endl;

	}


	fout.close();

	// Saving Patient History

	fout.open(pHistoryFile);


	for (int i = 0; i < patientCount; i++) {
	
		if (patients[i].getHasHistory()) {
		

			pRecord** history = patients[i].getHistory();
			int historySize = patients[i].getHistorySize();

			fout << patients[i].getPId() << " ";

			for (int j = 0; j < historySize; j++) {
			
				fout
					<< history[j][0].getDiseaseType() << " "
					<< history[j][0].getVisDate().getDay() << " "
					<< history[j][0].getVisDate().getMonth() << " "
					<< history[j][0].getVisDate().getYear() << " "
					<< history[j][0].getVisTime().getHour() << " "
					<< history[j][0].getVisTime().getMin() << " "
					<< history[j][0].getVisTime().getSec() << " "
					<< history[j][0].getAssignedDoc() << " "
					<< history[j][0].getFeePaid();

				if (j < historySize - 1) fout << " ";
			
			}


			if (i < patientCount - 1) fout << endl;

		
		}

	}

	fout.close();


	// Saving Patients Visited

	fout.open(pVisitedFile);

	for (int i = 0; i < docCount; i++) {
		
		fout << doctors[i].getDId() << " ";

		if (doctors[i].getPatientsVisitedSize() > 0) {
			
			for (int j = 0;
				j < doctors[i].getPatientsVisitedSize();
				j++) {
			
				fout << doctors[i].getPatientsVisited()[j] << " ";

			}

		}
		else {
		
			fout << 0;

		}

		if (i < docCount - 1) fout << endl;

	}


	fout.close();


}

Clinic::~Clinic() {

	if (patientCount > 0) delete[] patients;
	if (docCount > 0) delete[] doctors;
	if (aptCount > 0) delete[] apts;

}
