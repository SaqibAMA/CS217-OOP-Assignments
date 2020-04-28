#pragma once

#include <iostream>
#include "Date.h"
#include "mTime.h"

using namespace std;

class pRecord {
private:
	char* DiseaseType;
	Date visDate;
	mTime visTime;
	int AssignedDoc;
	float feePaid;

public:

	// Constructors
	pRecord();
	pRecord(char*, Date&, mTime&, int, float);
	pRecord(const pRecord&);

	// Getters and Setters
	char* getDiseaseType();
	Date getVisDate();
	mTime getVisTime();
	int getAssignedDoc();
	float getFeePaid();

	void setDiseaseType(char*);
	void setVisDate(Date&);
	void setVisTime(mTime&);
	void setAssignedDoc(int);
	void setFeePaid(float);

	// Operators
	pRecord& operator = (pRecord&);
	friend ostream& operator << (ostream&, const pRecord&);
	
	// Destructors
	~pRecord();
};

