#include "Date.h"


Date::Date() {
	
	day = 1;
	month = 1;
	year = 1999;

}

Date::Date(int day, int month, int year) {
	
	this->day = day;
	this->month = month;
	this->year = year;

}

Date::Date(const Date& D) {
	
	this->day = D.day;
	this->month = D.month;
	this->year = D.year;

}

Date::Date(char* str) {
	
	char buff[5];
	int dmy[3], dmyInd = 0;

	for (int i = 0; i <= strlen(str); i++) {
		
		int j = 0;
		while (str[i] != '/' && str[i] != '\0') {
		
			buff[j++] = str[i++];

		}
		buff[j] = '\0';

		dmy[dmyInd++] = atoi(buff);

	}

	this->day = (dmy[0] >= 1 && dmy[0] <= 31) ? dmy[0] : 1;
	this->month = (dmy[1] >= 1 && dmy[1] <= 12) ? dmy[1] : 1;
	this->year = (dmy[2] >= 1 && dmy[2] <= 9999) ? dmy[2] : 1;

}


int Date::getDay() {return day;}
int Date::getMonth() {return month;}
int Date::getYear() {return year;}

void Date::setDay(int day) {

	this->day = (day >= 1 && day <= 31) ? day : 1;

}

void Date::setMonth(int month) {

	this->month = (month >= 1 && month <= 12) ? month : 1;

}

void Date::setYear(int year) {

	this->year = (year >= 1 && year <= 9999) ? year : 1;

}


ostream& operator << (ostream& out, const Date& D) {
	
	out << D.day << "/" << D.month << "/" << D.year;

	return out;

}

istream& operator >> (istream& in, Date& D) {
	
	char str[15];
	in >> str;

	char buff[5];
	int dmy[3], dmyInd = 0;

	for (int i = 0; i <= strlen(str); i++) {
		
		int j = 0;
		while (str[i] != '/' && str[i] != '\0') {
		
			buff[j++] = str[i++];

		}
		buff[j] = '\0';

		dmy[dmyInd++] = atoi(buff);

	}

	D.day = (dmy[0] >= 1 && dmy[0] <= 31) ? dmy[0] : 1;
	D.month = (dmy[1] >= 1 && dmy[1] <= 12) ? dmy[1] : 1;
	D.year = (dmy[2] >= 1 && dmy[2] <= 9999) ? dmy[2] : 1;

	return in;

}


Date::~Date() {

	day = 0;
	month = 0;
	year = 0;

}
