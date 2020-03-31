#include "MyString.h"


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

MyString& MyString::operator = (const MyString& str) {
	
	delete[] this->strArray;
	this->strArray = new char[strlen(str.strArray) + 1];

	int i;
	for (i = 0; i < str.length; i++)
		this->strArray[i] = str.strArray[i];
	this->strArray[i] = '\0';

	this->length = str.length;

	return *this;

}

MyString MyString::operator + (const MyString& str) {
	
	int totalLen = this->length + str.length;
		
	char* str3 = new char[totalLen];

	int i;
	for (i = 0; i < this->length && this->strArray[i] != '\0'; i++)
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
	for (i = 0; i < this->length && this->strArray[i] != '\0'; i++)
		str3[i] = this->strArray[i];

	for (int j = 0; j < strlen(str); i++, j++)
		str3[i] = str[j];

	str3[i] = '\0';

	MyString tempStr(str3);

	return tempStr;

}

MyString MyString::operator - (char* str) {
	
	int strSize = strlen(str) - 1;
	bool stringFound;

	char* tempStr = new char[this->length + 1];
	for (int i = 0; i <= this->length && this->strArray[i] != '\0'; i++)
		tempStr[i] = this->strArray[i];


	for (int i = 0; i < this->length; i++) {
		
		stringFound = true;

		for (int j = i; j < i + strSize && stringFound; j++) {
			
			if (tempStr[j] != str[j - i]) stringFound = false;

		}

		if (stringFound) {
			
			int k = i;
			while (k < this->length - strSize) {
				
				tempStr[k] = tempStr[k + strSize];

				k++;
			}

		}

	}

	MyString temp(tempStr);
	delete[] tempStr;

	return temp;

}

MyString MyString::operator - (const MyString& str) {
	
	MyString temp(*this - str.strArray);
	return temp;

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


bool MyString::operator > (const MyString& str) {
	
	char temp1, temp2;

	for (int i = 0; i < length && i < str.length; i++) {
		
		temp1 = strArray[i];
		temp2 = str.strArray[i];

		if (temp1 < 'a') strArray[i] += 32;
		if (temp2 < 'a') str.strArray[i] += 32;

		if (temp1 < temp2) return false;

	}

	return !(str.length > length);

}

bool MyString::operator < (const MyString& str) {
	return !(*this > str);
}


char& MyString::operator [] (const int i) {

	if (i >= 0 && i < length) {
		return strArray[i];
	}
	else {
		cerr << "Index out of bounds!" << endl;
		return strArray[0];
	}

}

const char& MyString::operator [] (const int i) const {

	if (i >= 0 && i < length) {
		return strArray[i];
	}
	else {
		cerr << "Index out of bounds!" << endl;
		return strArray[0];
	}

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

	for (int i = 0; i < str.length; i++)
		out << str.strArray[i];
	out << endl;

	return out;

}

ifstream& operator >> (ifstream& in, MyString& str) {

	char buff[100];
	in.getline(buff, 100);

	delete[] str.strArray;
	str.strArray = new char[str.strlen(buff)];

	int i;
	for (i = 0; buff[i] != '\0'; i++)
		str.strArray[i] = buff[i];
	
	str.strArray[i] = '\0';

	str.length = str.strlen(buff);

	in.ignore();

	return in;

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