#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class MyString {
	
private:
	char* strArray;
	int length;

public:

	// Constructors
	MyString();
	MyString(char* str);
	MyString(const MyString&);

	// Operators
	MyString operator + (const MyString&);
	MyString operator + (char*);

	MyString operator - (const MyString&);
	MyString operator - (char*);

	MyString& operator = (const MyString& str);

	bool operator == (const MyString&);
	bool operator != (const MyString&);

	bool operator > (const MyString&);
	bool operator < (const MyString&);

	char& operator [] (const int i);
	const char& operator [] (const int i) const;

	// Stream insertion operators
	friend ostream& operator << (ostream&, const MyString&);
	friend istream& operator >> (istream&, MyString&);

	friend ofstream& operator << (ofstream&, const MyString&);
	friend ifstream& operator >> (ifstream&, MyString&);

	// Destructors
	~MyString();


	// Helper functions
	int strlen(char* str);


};
