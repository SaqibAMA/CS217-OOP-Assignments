#pragma once

#include <iostream>
#include <cstring>
#include "Name.h"
#include "Date.h"

using namespace std;

class Person
{
private:
	Name pName;
	Date DOB;
	int age;
	int ID;

public:
	// Constructors
	Person();
	Person(Name&, Date&, int, int);
	Person(const Person&);

	// Getters and Setters
	Name getPName();
	Date getDOB();
	int getAge();
	int getID();

	void setPName(Name&);
	void setDOB(Date&);
	void setAge(int);
	void setID(int);


	// Operators
	friend ostream& operator << (ostream&, const Person&);
	friend istream& operator >> (istream&, Person&);


	// Destructor
	~Person();
};

