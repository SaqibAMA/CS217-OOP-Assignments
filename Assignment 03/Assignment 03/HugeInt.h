// program bugs when you only enter 0

#pragma once

#include <iostream>
#include <cstring>

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

	// Operators
	int operator[](const int);

	HugeInt& operator = (const HugeInt&);
	bool operator == (const HugeInt&);
	bool operator != (const HugeInt&);
	bool operator < (const HugeInt&);
	bool operator > (const HugeInt&);
	bool operator <= (const HugeInt&);
	bool operator >= (const HugeInt&);

	// Helper functions
	void print();
	int getNumLength(int);

	// Stream insertion & extraction
	friend ostream& operator << (ostream&, const HugeInt&);
	friend istream& operator >> (istream&, HugeInt&);

	// Destructors
	~HugeInt();
};

