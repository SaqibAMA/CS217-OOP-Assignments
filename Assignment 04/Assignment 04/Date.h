#pragma once

#include <iostream>
#include <cstring>

using namespace std;

class Date {

private:
	int day;
	int month;
	int year;

public:

	// Constructors
	Date();
	Date(int, int, int);
	Date(const Date&);
	Date(char*);

	// Getters and Setters
	int getDay();
	int getMonth();
	int getYear();
	void setDay(int);
	void setMonth(int);
	void setYear(int);

	// Operators
	friend ostream& operator << (ostream&, const Date&);
	friend istream& operator >> (istream&, Date&);

	// Destructor
	~Date();
};

