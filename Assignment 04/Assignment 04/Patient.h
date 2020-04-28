#pragma once
#include "Person.h"
#include "pRecord.h"

class Patient : public Person
{
private:
	int pId;
	pRecord** history;
	int historySize;
	bool hasHistory;
public:
	// Constructors
	Patient();
	Patient(const Patient&);
	Patient(int, pRecord**, int);
	Patient(int, Name&, Date&, int, int, bool);

	// Getters and Setters
	int getPId() const;
	pRecord** getHistory() const;
	int getHistorySize() const;
	bool getHasHistory() const;

	void setPId(int);
	void setHistory(pRecord**, int);
	void setHistorySize(int);
	void setHasHistory(bool);

	// Member functions
	void addRecord(char*, Date&, mTime&, int, float);
	void printRecords() const;
	bool isUniqueID(Patient**, int, int);

	// Output operator
	friend ostream& operator << (ostream&, const Patient&);
	Patient& operator = (Patient&);

	// Destructor
	~Patient();
};

