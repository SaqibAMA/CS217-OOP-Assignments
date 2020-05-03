#pragma once
#include "Person.h"
class Doctor :
	public Person
{
private:
	int dId;
	char* specialization;
	int* patientsVisited;
	int patientsVisitedSize;
public:
	
	// Constructors
	Doctor();
	Doctor(int dId, Name, Date, int, int, char*);
	Doctor(const Doctor&);


	// implement constructors
	// and operators


	// Getters and Setters
	int getDId() const;
	char* getSpecialization() const;
	int* getPatientsVisited() const;
	int getPatientsVisitedSize() const;

	void setDId(int);
	void setSpecialization(char*);
	void setPatientsVisited(int*, int);
	void setPatientsVisitedSize(int);
	void addPatientVisited(int);

	// Output Operator
	friend ostream& operator << (ostream&, const Doctor&);
	Doctor& operator = (Doctor&);
	
	// Destructor
	~Doctor();
};

