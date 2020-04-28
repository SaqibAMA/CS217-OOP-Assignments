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

		apts[i].setStatus(atoi(buff));

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
			tempRecord.setFeePaid(atof(buff));

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
		
		cout << "Appointment ->" << i + 1 << "\n\n";
		cout << "Doc ID -> " << apts[i].getDiD() << endl;
		cout << "Patient ID -> " << apts[i].getPiD() << endl;
		cout << "Apt. Date -> " << apts[i].getAppDate() << endl;
		cout << "Apt. Time -> " << apts[i].getAppTime() << endl;
		cout << "Disease Type -> " << apts[i].getDiseaseType() << endl;
		cout << "Token No. -> " << apts[i].getTokenNumber() << endl;
		cout << "Fee -> " << apts[i].getFee() << endl;
		cout << "Status -> " << apts[i].getStatus() << endl;

	}

}

void Clinic::printDoctors() {
	
	for (int i = 0; i < docCount; i++) {
		
		cout << doctors[i] << endl;
		
	}

}

void Clinic::printPatients() {
	
	for (int i = 0; i < patientCount; i++) {
		
		cout << patients[i] << endl;

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

bool Clinic::patientIDIsUnique(int i) {

	for (int i = 0; i < patientCount; i++) {
		
		if (i == patients[i].getPId()) return false;

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
		cout << apts[i].getAppDate() << " ";
		cout << apts[i].getAppTime() << "\t\t";
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

	patients = _patients;

}

Clinic::~Clinic() {

	if (patientCount > 0) delete[] patients;
	if (docCount > 0) delete[] doctors;
	if (aptCount > 0) delete[] apts;

}
