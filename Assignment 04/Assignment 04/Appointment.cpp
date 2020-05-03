#include "Appointment.h"


Appointment::Appointment() {
	DiseaseType = new char('\0');
	pId = 0;
	dId = 0;
	tokenNumber = 0;
	fee = 0;
	status = 0;
}

Appointment::Appointment(char* DiseaseType, int pId, int dId, Date& appDate, mTime& appTime, int tokenNumber, float fee, bool status) {
	
	if (DiseaseType[0] == '\0') {
		this->DiseaseType = new char('\0');
	} else {
		this->DiseaseType = new char[strlen(DiseaseType) + 1];
		strcpy(this->DiseaseType, DiseaseType);
	}

	this->appDate = appDate;
	this->appTime = appTime;

	this->pId = pId;
	this->dId = dId;
	this->tokenNumber = tokenNumber;
	this->fee = fee;
	this->status = status;

}

Appointment::Appointment(const Appointment& A) {

	if (A.DiseaseType[0] == '\0') {
		this->DiseaseType = new char('\0');
	} else {
		this->DiseaseType = new char[strlen(A.DiseaseType) + 1];
		strcpy(this->DiseaseType, A.DiseaseType);
	}

	this->appDate = A.appDate;
	this->appTime = A.appTime;

	this->pId = A.pId;
	this->tokenNumber = A.tokenNumber;
	this->fee = A.fee;
	this->status = A.status;

}


char* Appointment::getDiseaseType() const {
	return DiseaseType;
}

int Appointment::getPiD() const {
	return pId;
}

int Appointment::getDiD() const {
	return dId;
}

Date Appointment::getAppDate() const {
	return appDate;
}

mTime Appointment::getAppTime() const {
	return appTime;
}

int Appointment::getTokenNumber() const {
	return tokenNumber;
}

float Appointment::getFee() const {
	return fee;
}

bool Appointment::getStatus() const {
	return status;
}

void Appointment::setDiseaseType(char* DiseaseType) {
	
	if (DiseaseType[0] == '\0') {

		this->DiseaseType = new char('\0');
	
	} else {
		
		this->DiseaseType = new char[strlen(DiseaseType) + 1];
		strcpy(this->DiseaseType, DiseaseType);

	}

}

void Appointment::setPiD(int pId) {
	
	this->pId = pId;

}

void Appointment::setDiD(int dId) {
	
	this->dId = dId;

}

void Appointment::setAppDate(Date& appDate) {
	
	this->appDate = appDate;

}

void Appointment::setAppTime(mTime& appTime) {

	this->appTime = appTime;

}

void Appointment::setTokenNumber(int tokenNumber) {
	
	this->tokenNumber = tokenNumber;

}

void Appointment::setFee(float fee) {
	
	this->fee = fee;

}

void Appointment::setStatus(bool status) {
	
	this->status = status;

}


Appointment& Appointment::operator = (Appointment& A) {
	
	this->setDiseaseType(A.getDiseaseType());
	this->setPiD(A.getPiD());
	this->setDiD(A.getDiD());
	this->setAppDate(A.getAppDate());
	this->setAppTime(A.getAppTime());
	this->setTokenNumber(A.getTokenNumber());
	this->setFee(A.getFee());
	this->setStatus(A.getStatus());

	return *this;

}

ostream& operator << (ostream& out, const Appointment& A) {
	
	out << "Appointment Details-> " << endl;
	out << "Disease Type-> " << A.DiseaseType << endl;
	out << "Patient ID-> " << A.pId << endl;
	out << "Doctor ID-> " << A.dId << endl;
	out << "Token Number-> " << A.tokenNumber << endl;
	out << "Fee -> " << A.fee << endl;
	out << "Appointment Status-> ";
	(A.status) ? out << "Completed." << endl : out << "Pending." << endl;
	out << "Appointment Time-> " << A.appTime << endl;
	out << "Appointment Date-> " << A.appDate << endl;


	return out;

}

Appointment::~Appointment() {

	delete[] DiseaseType;

}
