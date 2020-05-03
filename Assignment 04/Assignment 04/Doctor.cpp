#include "Doctor.h"


Doctor::Doctor() {
	
	dId = 0;
	specialization = new char('\0');
	patientsVisited = nullptr;
	patientsVisitedSize = 0;

}

// DID, fname, lname, day, month, year, Age, Nid, specialization
Doctor::Doctor(int dId, Name pName, Date DOB, int age, int nId, char* specialization) : Person (pName, DOB, age, nId){
	
	this->dId = dId;
	this->patientsVisited = nullptr;
	this->patientsVisitedSize = 0;

	if (specialization[0] == '\0') {
		this->specialization = new char('\0');
	} else {
		this->specialization = new char[strlen(specialization) + 1];
		strcpy(this->specialization, specialization);
	}

}

Doctor::Doctor(const Doctor& D)
	: Person(D.Person::getPName(), D.Person::getDOB(),
	D.Person::getAge(), D.Person::getID()) {
		
		this->dId = D.dId;

		if (D.specialization[0] == '\0') {
			
			this->specialization = new char('\0');

		} else {
			
			this->specialization = new char[strlen(D.specialization) + 1];
			strcpy(this->specialization, D.specialization);

		}

		this->patientsVisitedSize = D.patientsVisitedSize;

		if (D.patientsVisitedSize > 0) {
			
			this->patientsVisited = new int[this->patientsVisitedSize];
			for (int i = 0; i < this->patientsVisitedSize; i++)
				this->patientsVisited[i] = D.patientsVisited[i];


		} else {
			
			this->patientsVisited = nullptr;

		}

}

int Doctor::getDId() const {
	return dId;
}
char* Doctor::getSpecialization() const {
	return specialization;
}
int* Doctor::getPatientsVisited() const {
	return patientsVisited;
}
int Doctor::getPatientsVisitedSize() const {
	return patientsVisitedSize;
}

void Doctor::setDId(int dId) {

	this->dId = dId;

}
void Doctor::setSpecialization(char* specialization) {
	
	delete this->specialization;
	this->specialization = new char[strlen(specialization) + 1];
	strcpy(this->specialization, specialization);

}

void Doctor::setPatientsVisited(int* patientsVisited, int patientsVisitedSize) {
	
	if (this->patientsVisited != nullptr)
		delete[] this->patientsVisited;
	
	this->patientsVisitedSize = patientsVisitedSize;

	if (patientsVisitedSize > 0) {
		this->patientsVisited = new int[patientsVisitedSize];
	} else {
		this->patientsVisited = nullptr;
	}

	for (int i = 0; i < patientsVisitedSize; i++) {
		this->patientsVisited[i] = patientsVisited[i];
	}
	

}

void Doctor::addPatientVisited(int patient) {
	
	if (this->patientsVisited == nullptr) {
	
		this->patientsVisitedSize = 1;
		this->patientsVisited = new int(patient);

	} else {
		
		int* _patientsVisited = new int[this->patientsVisitedSize + 1];
		
		for (int i = 0; i < this->patientsVisitedSize; i++) {
			_patientsVisited[i] = this->patientsVisited[i];
		}

		_patientsVisited[this->patientsVisitedSize] = patient;

		this->patientsVisitedSize++;

		delete[] this->patientsVisited;
		this->patientsVisited = _patientsVisited;

	}

}

void Doctor::setPatientsVisitedSize(int patientsVisited) {

	this->patientsVisitedSize = patientsVisitedSize;

}

ostream& operator << (ostream& out, const Doctor& D) {
	
	out << "\n\nDetails -> \n\n";
	out << "Name -> " << D.Person::getPName() << endl;
	out << "Date of Birth -> " << D.Person::getDOB() << endl;
	out << "Age -> " << D.Person::getAge() << endl;
	out << "ID -> " << D.Person::getID() << endl;
	out << "Doc ID -> " << D.getDId() << endl;
	out << "Specialization -> " << D.getSpecialization() << endl;
	
	if (D.patientsVisitedSize > 0) {
		
		out << "Patients visited -> ";
		for (int i = 0; i < D.patientsVisitedSize; i++)
			out << (D.patientsVisited)[i] << " ";
		out << endl;

	}

	return out;
}

Doctor& Doctor::operator = (Doctor& D) {
	
	this->setPName(D.getPName());
	this->setDOB(D.getDOB());
	this->setAge(D.getAge());
	this->setID(D.getID());
	
	this->setDId(D.getDId());
	this->setSpecialization(D.getSpecialization());
	this->setPatientsVisited(D.getPatientsVisited(), D.getPatientsVisitedSize());

	return *this;

}

Doctor::~Doctor() {

	delete[] specialization;

	if (patientsVisitedSize > 0)
		delete[] patientsVisited;

	
}
