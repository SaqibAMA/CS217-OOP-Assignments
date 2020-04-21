#include "Name.h"


Name::Name() {

	fName = new char('\0');
	lName = new char('\0');

}

Name::Name(char* fName, char* lName) {

	this->fName = new char[strlen(fName) + 1];
	strcpy(this->fName, fName);

	this->lName = new char[strlen(lName) + 1];
	strcpy(this->lName, lName);

}

Name::Name(const Name& N) {

	// Handling fName

	if (N.fName[0] == '\0') {
	
		this->fName = new char('\0');

	} else {
		
		this->fName = new char[strlen(N.fName) + 1];
		strcpy(this->fName, N.fName);

	}

	// Handling lName

	if (N.lName[0] == '\0') {
	
		this->lName = new char('\0');

	} else {
		
		this->lName = new char[strlen(N.lName) + 1];
		strcpy(this->lName, N.lName);

	}



}



char* Name::getFirstName() {return fName;}

char* Name::getLastName() {return lName;}

void Name::setFirstName(char* fName) {

	delete[] this->fName;

	if (fName[0] == '\0') {
		
		this->fName = new char('\0');

	} else {
		
		this->fName = new char[strlen(fName) + 1];
		strcpy(this->fName, fName);

	}

}

void Name::setLastName(char* lName) {

	delete[] this->lName;

	if (lName[0] == '\0') {
		
		this->lName = new char('\0');

	} else {
		
		this->lName = new char[strlen(lName) + 1];
		strcpy(this->lName, lName);

	}

}

ostream& operator << (ostream& out, const Name& N) {
	
	out << N.fName << " " << N.lName;

	return out;

}

istream& operator >> (istream& in, Name& N) {

	char buff[100];
	in >> buff;

	delete[] N.fName;
	N.fName = new char[strlen(buff) + 1];
	strcpy(N.fName, buff);


	in >> buff;

	delete[] N.lName;
	N.lName = new char[strlen(buff) + 1];
	strcpy(N.lName, buff);

	return in;
}

Name::~Name() {

	delete[] fName;
	delete[] lName;

}
