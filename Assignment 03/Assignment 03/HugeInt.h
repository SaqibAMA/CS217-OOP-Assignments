// program bugs when you only enter 0

#pragma once

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class HugeInt
{
private:
	int* ptr;
	int length;
	int rows;
	int maxLen;

	// 0 for positive
	// 1 for negative
	bool polarity;

public:
	// Constructors
	HugeInt();
	HugeInt(int);
	HugeInt(const HugeInt&);
	HugeInt(int*, int, bool);

	// Operators
	int operator[](const int);

	HugeInt& operator = (const HugeInt&);
	bool operator == (const HugeInt&);
	bool operator != (const HugeInt&);

	// make relational ones
	// for int as well
	bool operator < (const HugeInt&);
	bool operator > (const HugeInt&);
	bool operator <= (const HugeInt&);
	bool operator >= (const HugeInt&);

	// Helper functions
	int getNumLength(int);
	int getDigit(int, int);

	// Arithmetic

	// + operator has a dependecy on - operator
	// There is an issue when we add negative numbers into
	// positive numbers
	HugeInt operator + (const int);

	// This gives wrong results
	HugeInt operator + (HugeInt&);

	// This is obsolete because operator + is obsolete
	HugeInt operator * (const int);

	// Stream insertion & extraction
	friend ostream& operator << (ostream&, const HugeInt&);
	friend istream& operator >> (istream&, HugeInt&);

	// Destructors
	~HugeInt();
};

