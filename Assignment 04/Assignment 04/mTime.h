#pragma once

#include <iostream>
#include <cstring>

using namespace std;

class mTime
{
private:
	int hour;
	int min;
	int sec;

public:
	// Constructors
	mTime();
	mTime(int, int, int);
	mTime(const mTime&);

	// Getters and Setters
	int getHour();
	int getMin();
	int getSec();
	void setHour(int);
	void setMin(int);
	void setSec(int);

	// Operators
	friend ostream& operator << (ostream&, const mTime&);
	friend istream& operator >> (istream&, mTime&);

	// Destructor
	~mTime();
};

