#include "HugeInt.h"


HugeInt::HugeInt() {

	ptr = new int(0);
	length = 0;
	maxLen = 50;
	polarity = 0;
	rows = 1;

}

HugeInt::HugeInt(int x) {
	
	ptr = new int(abs(x));
	length = getNumLength(x);
	maxLen = 50;
	polarity = (x < 0);
	rows = (int) ceil(length / 9.0);


}

HugeInt::HugeInt(const HugeInt& H) {

	this->length = H.length;
	this->maxLen = H.maxLen;
	this->polarity = H.polarity;
	this->rows = H.rows;
	
	this->ptr = new int[rows];
	for (int i = 0; i < rows; i++)
		this->ptr[i] = H.ptr[i];

}

// problematic
int HugeInt::operator[](const int i) {
	
	int remLen = length - getNumLength(ptr[rows - 1]);
	int sub = i - getNumLength(ptr[rows - 1]);


	return sub;

}

HugeInt& HugeInt::operator = (const HugeInt& H) {

	delete [] this->ptr;
	this->length = H.length;
	this->rows = H.rows;
	this->polarity = H.polarity;

	this->ptr = new int[rows];
	for (int i = 0; i < this->rows; i++)
		this->ptr[i] = H.ptr[i];

	return *this;

}

bool HugeInt::operator == (const HugeInt& H) {

	if ((this->length != H.length) || (this->polarity != H.polarity)) {
		
			return false;

	}

	for (int i = 0; i < rows; i++) {
	
		if (this->ptr[i] != H.ptr[i]) return false;

	}

	return true;

}

bool HugeInt::operator != (const HugeInt& H) {

	return !(*this == H);

}

bool HugeInt::operator < (const HugeInt& H) {
	
	if ((this->length > H.length) ||
		(this->polarity == 0 && H.polarity == 1)) return false;

	if (this->length < H.length) return true;

	if (this->length == H.length) {
	
		for (int i = rows - 1; i >= 0; i--) {
		
			if (this->ptr[i] < H.ptr[i]) {
				return true;
			}

		}

	}

	return false;

}

bool HugeInt::operator > (const HugeInt& H) {
	
	return !(*this < H);

}

bool HugeInt::operator <= (const HugeInt& H) {
	
	return ((*this == H) || (*this < H));

}

bool HugeInt::operator >= (const HugeInt& H) {
	
	return ((*this > H) || (*this == H));

}

void HugeInt::print() {
	
	cout << "number-> ";

	for (int i = rows - 1; i >= 0; i--)
		cout << ptr[i];

	cout << "\npolarity-> ";
	cout << polarity << endl;

	cout << "length-> ";
	cout << length << endl;
	

}

int HugeInt::getNumLength(int n) {

	int len = 1;
	n = abs(n);

	while (n > 9) {
		
		n /= 10;
		++len;

	}

	return len;

}


ostream& operator << (ostream& out, const HugeInt& H) {

	(H.polarity == 1)? cout << "-" : cout << "+";
	for (int i = H.rows - 1; i >= 0; i--) {
		
		if (H.ptr[i] != 0) out << H.ptr[i] << " ";
		else out << "000000000" << " ";
	
	}

	return out;

}

istream& operator >> (istream& in, HugeInt& H) {

	char buff[51];
	in.getline(buff, 51);

	(buff[0] == '-') ? H.polarity = 1 : H.polarity = 0;

	int start = (buff[0] == '-' || buff[0] == '+');
	if (start) buff[0] = '0';

	while (buff[0] == '0') {
				
		int j = 0;
		while (j < strlen(buff)) {
				
			buff[j] = buff[j + 1];
			j++;

		}

	}

	int buffLen = strlen(buff);

	delete[] H.ptr;

	H.rows = (int) ceil(buffLen / 9.0);
	H.ptr = new int[H.rows];
	
	if (buffLen < 9) {
		
		H.ptr[0] = abs(atoi(buff));


	} else {
		

		for (int i = start, rowCount = 0; i < buffLen; i += 9) {
		
			int temp = 0;
			for (int j = buffLen - 1 - i, k = 0; j > buffLen - 10 - i && j >= 0; j--, k++) {
		
				temp += (buff[j] - 48) * (int)(pow(10, k));

			}

			H.ptr[rowCount++] = abs(temp);

		}


	}

	
	H.length = buffLen;

	return in;

}

HugeInt::~HugeInt() {

	delete[] ptr;
	length = 0;

}
