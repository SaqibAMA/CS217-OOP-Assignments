#include <iostream>
#include <cstring>

using namespace std;

#pragma once

class Name
{
private:
	char* fName;
	char* lName;
public:

	// Constructors
	Name();
	Name(char*, char*);
	Name(const Name&);

	// Getters and Setters
	char* getFirstName();
	char* getLastName();
	void setFirstName(char*);
	void setLastName(char*);

	// Operators
	friend ostream& operator << (ostream&, const Name&);
	friend istream& operator >> (istream&, Name&);

	// Destructor
	~Name();
};

