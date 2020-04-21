#include "mTime.h"


mTime::mTime() {
	
	hour = 0;
	min = 0;
	sec = 0;

}

mTime::mTime(int hour, int min, int sec) {
	
	this->hour = hour;
	this->min = min;
	this->sec = sec;

}

mTime::mTime(const mTime& T) {
	
	this->hour = T.hour;
	this->min = T.min;
	this->sec = T.sec;

}

int mTime::getHour() {return hour;}
int mTime::getMin() {return min;}
int mTime::getSec() {return sec;}

void mTime::setHour(int hour) {

	this->hour = (hour >= 0 && hour < 24) ? hour : 0;

}

void mTime::setMin(int min) {

	this->min = (min >= 0 && min <= 60) ? min : 0;

}

void mTime::setSec(int sec) {

	this->sec = (sec >= 0 && sec <= 60) ? sec : 0;

}


ostream& operator << (ostream& out, const mTime& T) {
	
	out << T.hour << ":" << T.min << ":" << T.sec;

	return out;

}

istream& operator >> (istream& in, mTime& T) {
	
	char str[15];
	in >> str;

	char buff[5];
	int dmy[3], dmyInd = 0;

	for (int i = 0; i <= strlen(str); i++) {
		
		int j = 0;
		while (str[i] != ':' && str[i] != '\0') {
		
			buff[j++] = str[i++];

		}
		buff[j] = '\0';

		dmy[dmyInd++] = atoi(buff);

	}

	T.hour = (dmy[0] >= 0 && dmy[0] < 24) ? dmy[0] : 0;
	T.min = (dmy[1] >= 0 && dmy[1] <= 60) ? dmy[1] : 0;
	T.sec = (dmy[2] >= 0 && dmy[2] <= 60) ? dmy[2] : 0;


	return in;

}


mTime::~mTime() {

	hour = 0;
	min = 0;
	sec = 0;

}
