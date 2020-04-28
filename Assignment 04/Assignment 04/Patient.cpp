#include "Patient.h"


Patient::Patient() {

	pId = 0;
	historySize = 0;
	hasHistory = 0;

}

Patient::Patient(const Patient& P) : Person(P.Person::getPName(), P.Person::getDOB(), P.Person::getAge(), P.Person::getID()) {

	this->pId = P.pId;

	if (P.historySize > 0) {
	
		this->history = new pRecord*[P.historySize];

		for (int i = 0; i < P.historySize; i++) {
		
			this->history[i] = new pRecord(P.history[0][i]);

		}

	}

	this->historySize = P.historySize;
	this->hasHistory = P.hasHistory;


}

Patient::Patient(int pId, pRecord** history, int historySize) {

	this->pId = pId;
	this->historySize = historySize;

	this->history = new pRecord*[historySize];
	for (int i = 0; i < historySize; i++)
		this->history[i] = new pRecord(history[i][0]);

	this->hasHistory = (historySize > 0);

}

Patient::Patient(int pId, Name& pName, Date& DOB, int age, int nId, bool hasHistory) : Person (pName, DOB, age, nId) {

	this->pId = pId;
	this->historySize = 0;

	this->hasHistory = hasHistory;

	// if the person has any history, handle that

}




int Patient::getPId() const {return pId;}
pRecord** Patient::getHistory() const {return history;}
int Patient::getHistorySize() const {return historySize;}
bool Patient::getHasHistory() const {return hasHistory;}


void Patient::setPId(int pId) {this->pId = pId;}
void Patient::setHistory(pRecord** history, int historySize) {

	if (this->historySize > 0) {
	
		for (int i = 0; i < this->historySize; i++)
			delete this->history[i];

		delete[] this->history;

	}

	
	this->historySize = historySize;
	this->history = new pRecord*[historySize];

	for (int i = 0; i < historySize; i++) {
	
		this->history[i] = new pRecord(history[i][0]);

	}

	this->hasHistory = (historySize > 0);


}
void Patient::setHistorySize(int historySize) {this->historySize = historySize;}
void Patient::setHasHistory(bool hasHistory) {this->hasHistory = hasHistory;}



bool Patient::isUniqueID(Patient** pList, int pListSize, int n) {

	for (int i = 0; i < pListSize; i++) {
	
		if (pList[i][0].pId == n) return false;

	}

	return true;

}

void Patient::addRecord(char* DiseaseType, Date& visDate, mTime& visTime, int AssignedDoc, float feePaid){

	pRecord newEntry(DiseaseType, visDate, visTime, AssignedDoc, feePaid);

	pRecord** _history = new pRecord*[historySize + 1];
	_history[historySize] = new pRecord(newEntry);

	for (int i = 0; i < historySize; i++) {
	
		_history[i] = new pRecord(history[i][0]);

	}

	if (historySize > 0) {
		for (int i = 0; i < historySize; i++)
			delete history[i];

		delete[] history;
	}

	history = _history;

	historySize++;

	this->hasHistory = (historySize > 0);

}

void Patient::printRecords() const {

	for (int i = 0; i < historySize; i++)
		cout << history[i][0] << endl;

}


ostream& operator << (ostream& out, const Patient& P) {

	out << "\n\nDetails -> \n\n";
	out << "Name -> " << P.Person::getPName() << endl;
	out << "Date of Birth -> " << P.Person::getDOB() << endl;
	out << "Age -> " << P.Person::getAge() << endl;
	out << "ID -> " << P.Person::getID() << endl;
	out << "Patient ID -> " << P.pId << endl;
	
	out << "\n\nHistory -> ";

	if (P.historySize > 0) {
		
		out << "\n\n";
		P.printRecords();

	} else {

		out << "None." << endl;

	}

	return out;


}

Patient& Patient::operator = (Patient& P) {
	
	this->setPName(P.getPName());
	this->setDOB(P.getDOB());
	this->setID(P.getID());
	this->setAge(P.getAge());

	this->pId = P.pId;
	this->hasHistory = P.hasHistory;
	this->historySize = P.historySize;


	if (hasHistory) {
		
		this->history = new pRecord*[P.historySize];

		for (int i = 0; i < historySize; i++)
			history[i] = new pRecord(P.history[i][0]);

	} else {
		
		this->history = nullptr;

	}

	return *this;


}

Patient::~Patient() {

	if (historySize > 0) {
		for (int i = 0; i < historySize; i++)
			delete history[i];

		delete[] history;
	}

}
