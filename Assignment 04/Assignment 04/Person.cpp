#include "Person.h"


Person::Person() {

	age = 0;
	ID = 0;

}

Person::Person(Name& N, Date& D, int age, int ID) {

	pName.setFirstName(N.getFirstName());
	pName.setLastName(N.getLastName());

	DOB.setDay(D.getDay());
	DOB.setMonth(D.getMonth());
	DOB.setYear(D.getYear());

	this->age = age;

	this->ID = ID;

}

Person::Person(const Person& P) {
	
	this->age = P.age;
	this->ID = P.ID;

	Name _pName(P.pName);

	this->pName.setFirstName(_pName.getFirstName());
	this->pName.setLastName(_pName.getLastName());

	Date _DOB(P.DOB);

	this->DOB.setDay(_DOB.getDay());
	this->DOB.setMonth(_DOB.getMonth());
	this->DOB.setYear(_DOB.getYear());

}


Name Person::getPName() {return pName;}
Date Person::getDOB() {return DOB;}
int Person::getAge() {return age;}
int Person::getID() {return ID;}

void Person::setPName(Name& N) {
	
	pName.setFirstName(N.getFirstName());
	pName.setLastName(N.getLastName());

}
void Person::setDOB(Date& D) {
	
	DOB.setDay(D.getDay());
	DOB.setMonth(D.getMonth());
	DOB.setYear(D.getYear());

}
void Person::setAge(int age) {
	
	this->age = age;

}
void Person::setID(int ID) {
	
	this->ID = ID;

}

ostream& operator << (ostream& out, const Person& P) {
	
	out << "PERSON DETAILS ->" << endl << endl;
	out << "NAME ->" << P.pName << endl;
	out << "DOB  ->" << P.DOB << endl;
	out << "AGE  ->" << P.age << endl;
	out << "ID   ->" << P.ID << endl;

	return out;
}

istream& operator >> (istream& in, Person& P) {
	
	cout << "NAME ->";
	in >> P.pName;
	cout << "DOB  ->";
	in >> P.DOB;
	cout << "AGE  ->";
	in >> P.age;
	cout << "ID   ->";
	in >> P.ID;

	return in;

}

Person::~Person() {

	age = 0;
	ID = 0;

}
