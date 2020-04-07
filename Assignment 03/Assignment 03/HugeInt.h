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
	bool isZero(const HugeInt&);
	bool isArrayGreater(int*, int, int*, int);

	// Arithmetic
	HugeInt operator + (const int);
	HugeInt operator + (HugeInt&);
	HugeInt operator * (const int);
	HugeInt operator * (HugeInt&);
	HugeInt operator - (const int);
	HugeInt operator - (HugeInt&);
	HugeInt operator / (HugeInt&);

	// Stream insertion & extraction
	friend ostream& operator << (ostream&, HugeInt&);
	friend istream& operator >> (istream&, HugeInt&);
	// friend HugeInt operator - (const int, HugeInt&);

	// Destructors
	~HugeInt();
};

