#pragma once

#include <iostream>
#include "Date.h"
#include "mTime.h"

using namespace std;

class Appointment
{
private:
	char * DiseaseType;
	int pId;
	int dId;
	Date appDate;
	mTime appTime;
	int tokenNumber;
	float fee;
	bool status;
public:
	// Constructors
	Appointment();
	Appointment(char*, int, int, Date&, mTime&, int, float, bool);
	Appointment(const Appointment&);

	// Getters and Setters

	char* getDiseaseType() const;
	int getPiD() const;
	int getDiD() const;
	Date getAppDate() const;
	mTime getAppTime() const;
	int getTokenNumber() const;
	float getFee() const;
	bool getStatus() const;

	void setDiseaseType(char*);
	void setPiD(int);
	void setDiD(int);
	void setAppDate(Date&);
	void setAppTime(mTime&);
	void setTokenNumber(int);
	void setFee(float);
	void setStatus(bool);

	// Operators
	Appointment& operator = (Appointment&);

	// Destructor
	~Appointment();
};

