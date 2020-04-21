#include "pRecord.h"


pRecord::pRecord() {

	DiseaseType = new char('\0');
	AssignedDoc = 0;
	feePaid = 0;

}

// create constructors and member functions


pRecord::~pRecord() {

	delete[] DiseaseType;
	
}
