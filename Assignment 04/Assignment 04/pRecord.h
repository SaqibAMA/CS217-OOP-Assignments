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

	// Destructors
	~pRecord();
};

