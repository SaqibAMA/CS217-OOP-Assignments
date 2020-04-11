#include <iostream>

using namespace std;

#pragma once

class HugeInt
{
public:

	// Constructors
	// Constructors
	HugeInt();
	HugeInt(int);
	HugeInt(const HugeInt&);
	HugeInt(int*, int, bool, bool);

	// Operators
	int operator[](const int);

	HugeInt& operator = (const HugeInt&);
	bool operator == (const HugeInt&);
	bool operator != (const HugeInt&);
	bool operator < (const HugeInt&);
	bool operator > (const HugeInt&);
	bool operator <= (const HugeInt&);
	bool operator >= (const HugeInt&);

	// Arithmetic
	HugeInt operator + (const int);
	HugeInt operator + (const HugeInt&);
	HugeInt operator * (const int);
	HugeInt operator * (const HugeInt&);
	HugeInt operator - (const int);
	HugeInt operator - (const HugeInt&);
	HugeInt operator / (const HugeInt&);

	// Helper functions
	int getNumLength(const int) const;
	bool isZero(const HugeInt&);
	bool isArrayGreater(int*, int, int*, int);


	// Stream insertion and extraction
	friend ostream& operator << (ostream&, const HugeInt&);
	friend istream& operator >> (istream&, HugeInt&);

	// Destructor
	~HugeInt();

private:
	int *ptr;
	int length;
	int rows;
	bool polarity;
};

