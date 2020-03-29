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

	bool operator == (const MyString&);
	bool operator != (const MyString&);

	char& operator [] (const int i);

	// Stream insertion operators
	friend ostream& operator << (ostream&, const MyString&);
	friend istream& operator >> (istream&, MyString&);

	friend ofstream& operator << (ofstream&, const MyString&);

	// Destructors
	~MyString();


	// Helper functions
	int strlen(char* str);


};

MyString::MyString() {

	strArray = new char('\0');
	length = 1;

}

MyString::MyString(char* str) {

	
	length = strlen(str);

	// Allocating memory for the string.
	strArray = new char[length];
	
	
	// Performing Deep Copy.

	int i;
	for (i = 0; str[i] != '\0'; i++)
		strArray[i] = str[i];
	
	// Null termination.
	strArray[i] = '\0';


}

MyString::MyString(const MyString& str) {

	length = strlen(str.strArray);

	this->strArray = new char[length];
		
	int i;
	for (i = 0; str.strArray[i] != '\0'; i++)
		this->strArray[i] = str.strArray[i];
	this->strArray[i] = '\0';

}


MyString MyString::operator + (const MyString& str) {
	
	int totalLen = this->length + str.length;
		
	char* str3 = new char[totalLen];

	int i;
	for (i = 0; i < this->length; i++)
		str3[i] = this->strArray[i];

	for (int j = 0; j < str.length; i++, j++)
		str3[i] = str.strArray[j];

	str3[i] = '\0';

	MyString tempStr(str3);

	return tempStr;

}

MyString MyString::operator + (char* str) {
	
	int totalLen = this->length + strlen(str);
		
	char* str3 = new char[totalLen];

	int i;
	for (i = 0; i < this->length; i++)
		str3[i] = this->strArray[i];

	for (int j = 0; j < strlen(str); i++, j++)
		str3[i] = str[j];

	str3[i] = '\0';

	MyString tempStr(str3);

	return tempStr;

}


bool MyString::operator == (const MyString& str) {

	cout << this->strArray << " " << str.strArray << endl;

	for (int i = 0; i < str.length; i++) {
		if (this->strArray[i] != str.strArray[i]) return false;
	}

	return true;

}

bool MyString::operator != (const MyString& str) {
	
	return !(*this == str);

}


char& MyString::operator [] (const int i) {

	if (i >= 0 && i < length)
		return strArray[i];
	else
		cerr << "Index out of bounds!" << endl;

}


ostream& operator << (ostream& out, const MyString& str) {

	out << str.strArray << endl;
	return out;

}

istream& operator >> (istream& in, MyString& str) {

	char buff[100];
	cin.getline(buff, 100);

	str.length = strlen(buff);

	delete[] str.strArray;

	str.strArray = new char[str.length + 1];

	int i;
	for (i = 0; i < str.length; i++)
		str.strArray[i] = buff[i];
	
	str.strArray[i] = '\0';

	return in;

}

ofstream& operator << (ofstream& out, const MyString& str) {

	for (int i = 0; i < str.length - 1; i++)
		out << str.strArray[i];

	return out;

}

MyString::~MyString() {
	
	delete strArray;
	length = 0;

}

int MyString::strlen(char *str) {
	
	int i = 0;
	while (str[i] != '\0') i++;

	return i + 1;

}

int main() {

	MyString str1("Saqib");

	MyString str2(str1);

	cout << "str1==str2: " << (str1 == str2) << endl;
	
	cout << ">> ";
	cin >> str2;

	cout << "str1==str2: " << (str1 == str2) << endl;

	cout << str1[55] << endl;

	ofstream fout;
	fout.open("data.txt");

	fout << str1 << endl;

	fout.close();
	
	return 0;
}