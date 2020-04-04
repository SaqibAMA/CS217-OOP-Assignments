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

HugeInt::HugeInt(int* H, int s, bool p) {
	

	this->maxLen = 50;
	this->polarity = p;


	// Clean up
	
	for (int i = 0; i < s && H[i] == 0;) {
		
		while (H[i] == 0) {
			
			for (int j = i; j < s - 1; j++) {
				
				H[j] = H[j + 1];

			}

			s--;

		}

	}

	this->length = s;
	this->rows = (int) ceil(length / 9.0);


	this->ptr = new int[rows];

	for (int i = 0, rowCount = 0; i < s; i += 9) {
		
		int temp = 0;
		for (int j = s - 1 - i, k = 0; j > s - 10 - i && j >= 0; j--, k++) {
		
			temp += H[j]* (int)(pow(10, k));

		}

		ptr[rowCount++] = abs(temp);

	}

}

int HugeInt::operator[](const int i) {
	
	if (i < getNumLength(ptr[rows - 1])) {
		
		int num = ptr[rows - 1];
		int l = getNumLength(num);
		

		while (l > i + 1) {
		
			num /= 10;
			l--;

		}

		return (num % 10);

	} else if (i < length){

		int _length = length - getNumLength(ptr[rows - 1]);
		int _i = i - getNumLength(ptr[rows - 1]);

		int index = _i % 9;
		int targetRow = (int)floor(_i / 9.0);
		
		int num = ptr[(rows - 2) - targetRow];

		int l = getNumLength(num);

		while (l > index + 1) {
			
			num /= 10;
			l--;

		}

		return (num % 10);


	}

	return 0;

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

int HugeInt::getNumLength(int n) {

	int len = 1;
	n = abs(n);

	while (n > 9) {
		
		n /= 10;
		++len;

	}

	return len;

}

int HugeInt::getDigit(int n, int ind) {

	if (ind < getNumLength(n)) {

		int l = getNumLength(n);
		
		while (l > ind + 1) {
		
			n /= 10;
			l--;

		}

		return (n % 10);

	}

	return 0;

}

// Arithmetic
HugeInt HugeInt::operator + (const int num) {


	if (num == 0) {
		
		return *this;

	} else if (this->polarity == 0 && num > 0) {
		
		int carry = 0;

		int numLen = getNumLength(num);
		int _length = this->length;

		int sumLen = (numLen > length) ? numLen + 2 : length + 2;

		/*cout << "numLen->" << numLen << endl;
		cout << "length->" << length << endl;
		cout << "sumLen->" << sumLen << endl;*/

		int* temp = new int [sumLen];

		for (int i = _length, j = 0; i >= 0; i--, j++) {


			/*cout << "(*this).ptr[_length - i - 1]: " << (*this)[_length - i - 1] << endl;
			cout << "digit: " << getDigit(num, numLen - 1 - i) << endl;
			*/


			temp[sumLen - j - 1] = carry + (*this)[_length - j - 1] + getDigit(num, numLen - 1 - j);

			carry = (temp[sumLen - j - 1] > 9);
			if (carry) temp[sumLen - j - 1] %= 10;


			/*cout << "stored->" << temp[sumLen - j - 1] << endl;
			cout << "index->" << sumLen - j - 1 << endl;*/

		}

		temp[0] = carry;

		for (int i = 0; i < sumLen && temp[i] == 0;) {
		
			while (temp[i] == 0) {
			
				for (int j = i; j < sumLen - 1; j++) {
				
					temp[j] = temp[j + 1];

				}

				sumLen--;

			}

			i = 0;

		}

		cout << "sum -> ";
		for (int i = 0; i < sumLen; i++)
			cout << temp[i];
		cout << endl;

		HugeInt tempObj;

		tempObj.rows = (int) ceil(sumLen/9.0);
		tempObj.ptr = new int [tempObj.rows];
		tempObj.polarity = 0;
		tempObj.length = sumLen;

		int numBuff = 0;

		for (int i = 0, rCount = 0; i < sumLen; i += 9, rCount++) {
			
			numBuff = 0;

			for (int j = sumLen - 1 - i, dCount = 0; j >= 0 && j >= sumLen - 10 - i; j--, dCount++) {
				
				numBuff += temp[j] * pow(10, dCount);
				cout << "numBuff-> " << numBuff << endl;

			}

			cout << "rCount-> " << rCount << endl;
			tempObj.ptr[rCount] = numBuff;

		}

		delete[] temp;

		return tempObj;


	}

	// remove this after a - b is implemented.
	return *this;

}

HugeInt HugeInt::operator + (HugeInt& H) {
	

	if (this->polarity == 0 && H.polarity == 0) {
		
		int carry = 0;

		int numLen = H.length;
		int _length = this->length;

		int sumLen = (numLen > length) ? numLen + 2 : length + 2;

		/*cout << "numLen->" << numLen << endl;
		cout << "length->" << length << endl;
		cout << "sumLen->" << sumLen << endl;*/

		int* temp = new int [sumLen];

		for (int i = _length, j = 0; i >= 0; i--, j++) {


			/*cout << "(*this).ptr[_length - i - 1]: " << (*this)[_length - i - 1] << endl;
			cout << "digit: " << getDigit(num, numLen - 1 - i) << endl;
			*/


			temp[sumLen - j - 1] = carry + (*this)[_length - j - 1] + H[numLen - 1 - j];

			carry = (temp[sumLen - j - 1] > 9);
			if (carry) temp[sumLen - j - 1] %= 10;


			/*cout << "stored->" << temp[sumLen - j - 1] << endl;
			cout << "index->" << sumLen - j - 1 << endl;*/

		}

		temp[0] = carry;

		for (int i = 0; i < sumLen && temp[i] == 0;) {
		
			while (temp[i] == 0) {
			
				for (int j = i; j < sumLen - 1; j++) {
				
					temp[j] = temp[j + 1];

				}

				sumLen--;

			}

			i = 0;

		}

		/*cout << "sum -> ";
		for (int i = 0; i < sumLen; i++)
			cout << temp[i];
		cout << endl;*/

		HugeInt tempObj;

		tempObj.rows = (int) ceil(sumLen/9.0);
		tempObj.ptr = new int [tempObj.rows];
		tempObj.polarity = 0;
		tempObj.length = sumLen;

		int numBuff = 0;

		for (int i = 0, rCount = 0; i < sumLen; i += 9, rCount++) {
			
			numBuff = 0;

			for (int j = sumLen - 1 - i, dCount = 0; j >= 0 && j >= sumLen - 9 - i; j--, dCount++) {
				
				numBuff += temp[j] * pow(10, dCount);
				/*cout << "numBuff-> " << numBuff << endl;*/

			}

			/*cout << "rCount-> " << rCount << endl;*/
			tempObj.ptr[rCount] = numBuff;
			/*cout << "ptr[rCount]: " << tempObj.ptr[rCount] << endl;*/

		}

		delete[] temp;

		return tempObj;


	}

	// remove this after a - b is implemented.
	return *this;


}

HugeInt HugeInt::operator * (const int n) {
	
	HugeInt temp(*this);

	for (int i = 0; i < n - 1; i++) {
	
		temp = temp + *this;

	}

	return temp;

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
				
		unsigned int j = 0;
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
