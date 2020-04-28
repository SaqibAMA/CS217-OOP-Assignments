#include "pRecord.h"


pRecord::pRecord() {

	DiseaseType = new char('\0');
	AssignedDoc = 0;
	feePaid = 0;

}

pRecord::pRecord(char* DiseaseType, Date& visDate, mTime& visTime, int AssignedDoc, float feePaid) {

	this->DiseaseType = new char[strlen(DiseaseType) + 1];
	strcpy(this->DiseaseType, DiseaseType);

	this->visDate.setDay(visDate.getDay());
	this->visDate.setMonth(visDate.getMonth());
	this->visDate.setYear(visDate.getYear());

	this->visTime.setHour(visTime.getHour());
	this->visTime.setMin(visTime.getMin());
	this->visTime.setSec(visTime.getSec());

	this->AssignedDoc = AssignedDoc;

	this->feePaid = feePaid;

}

pRecord::pRecord(const pRecord& P) {
	
	if (P.DiseaseType[0] != '\0') {
		this->DiseaseType = new char[strlen(P.DiseaseType) + 1];
		strcpy(this->DiseaseType, P.DiseaseType);
	} else {
		this->DiseaseType = new char('\0');
	}


	Date _visDate(P.visDate);

	this->visDate.setDay(_visDate.getDay());
	this->visDate.setMonth(_visDate.getMonth());
	this->visDate.setYear(_visDate.getYear());


	mTime _visTime(P.visTime);

	this->visTime.setHour(_visTime.getHour());
	this->visTime.setMin(_visTime.getMin());
	this->visTime.setSec(_visTime.getSec());

	this->AssignedDoc = P.AssignedDoc;

	this->feePaid = P.feePaid;

}

pRecord& pRecord::operator = (pRecord& P) {

	delete[] this->DiseaseType;

	if (P.DiseaseType[0] != '\0') {
		this->DiseaseType = new char[strlen(P.DiseaseType) + 1];
		strcpy(this->DiseaseType, P.DiseaseType);
	} else {
		this->DiseaseType = new char('\0');
	}


	Date _visDate(P.visDate);

	this->visDate.setDay(_visDate.getDay());
	this->visDate.setMonth(_visDate.getMonth());
	this->visDate.setYear(_visDate.getYear());

	mTime _visTime(P.visTime);

	this->visTime.setHour(_visTime.getHour());
	this->visTime.setMin(_visTime.getMin());
	this->visTime.setSec(_visTime.getSec());

	this->AssignedDoc = AssignedDoc;

	this->feePaid = feePaid;

	return *this;


}

char* pRecord::getDiseaseType() {return DiseaseType;}
Date pRecord::getVisDate() {return visDate;}
mTime pRecord::getVisTime() {return visTime;}
int pRecord::getAssignedDoc() {return AssignedDoc;}
float pRecord::getFeePaid() {return feePaid;}

void pRecord::setDiseaseType(char* DiseaseType) {

	if (DiseaseType[0] != '\0') {
		delete[] this->DiseaseType;
		this->DiseaseType = new char[strlen(DiseaseType) + 1];
		strcpy(this->DiseaseType, DiseaseType);
	}

}
void pRecord::setAssignedDoc(int AssignedDoc) {
	
	this->AssignedDoc = AssignedDoc;

}
void pRecord::setFeePaid(float feePaid) {
	this->feePaid = feePaid;
}
void pRecord::setVisDate(Date& visDate) {
	this->visDate.setDay(visDate.getDay());
	this->visDate.setMonth(visDate.getMonth());
	this->visDate.setYear(visDate.getYear());
}
void pRecord::setVisTime(mTime& visTime) {
	this->visTime.setHour(visTime.getHour());
	this->visTime.setMin(visTime.getMin());
	this->visTime.setSec(visTime.getSec());
}

ostream& operator << (ostream& out, const pRecord& P) {


	out << "Disease type -> " << P.DiseaseType << endl;
	out << "Visit date -> " << P.visDate << endl;
	out << "Visit time -> " << P.visTime << endl;
	out << "Assigned doc -> " << P.AssignedDoc << endl;
	out << "Fee paid -> " << P.feePaid << endl;
	

	return out;

}

pRecord::~pRecord() {

	delete[] DiseaseType;
	
}
