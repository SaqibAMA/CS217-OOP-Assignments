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

	if (isZero(H)) {
		
		HugeInt temp(0);
		*this = temp;

	}

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
				
				numBuff += temp[j] * (int)pow(10, dCount);
			//	cout << "numBuff-> " << numBuff << endl;

			}

			//cout << "rCount-> " << rCount << endl;
			tempObj.ptr[rCount] = numBuff;

		}

		delete[] temp;

		return tempObj;


	}

	// remove this after a - b is implemented.
	return *this;

}

bool HugeInt::isZero(const HugeInt& H) {
	
	for (int i = 0; i < H.rows; i++)
		if (H.ptr[i] != 0) return false;

	return true;
}

HugeInt HugeInt::operator + (HugeInt& H) {


	if (this->polarity == 0 && H.polarity == 0) {

		if(isZero(*this)) return H;
		if(isZero(H)) return *this;

		
		/*cout << "\n...Adding...\n" << endl;
		cout << *this << endl;
		cout << H << endl;*/
		
		int carry = 0;

		int numLen = H.length;
		int _length = this->length;

		int* tempA = new int[_length];
		int* tempB = new int[numLen];
		

		for (int i = 0; i < _length; i++) tempA[i] = -1;



		/// array copy me masla aaraha hai


		for (int i = 0, dCount = _length - 1; i < this->rows && dCount >= 0; i++, dCount -= 9) {
		
			

			for (int j = dCount, k = 8; j >= dCount - 9 && j >= 0; j--, k--) {
				
				if (ptr[i] == 0) {
					tempA[j] = 0;
				}
				else {

					tempA[j] = getDigit(ptr[i], k);

				}

				cout << tempA[j];


			}

			cout << endl;
			

		}

		cout << "tempA-> ";
		for (int i = 0; i < _length; i++) cout << tempA[i];
		cout << endl;

		/*cout << "tempB-> ";
		for (int i = 0; i < _length; i++) cout << tempB[i];
		cout << endl;*/

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

			for (int j = sumLen - 1 - i, dCount = 0; j >= 0 && j >= sumLen - 9 - i; j--, dCount++) {
				
				//cout << "temp[j]" << temp[j] << endl;
				//cout << "j: " << j << endl;

				numBuff += temp[j] * (int)pow(10, dCount);
				//cout << "numBuff-> " << numBuff << endl;

			}

			//cout << "rCount-> " << rCount << endl;
			tempObj.ptr[rCount] = numBuff;
			//cout << "ptr[rCount]: " << tempObj.ptr[rCount] << endl;

		}

		/*cout << "sum -> ";
		for (int i = 0; i < sumLen; i++)
			cout << temp[i];
		cout << endl;*/

		delete[] temp;

		return tempObj;


	}

	return *this;


}

HugeInt HugeInt::operator * (const int n) {

	if (n == 0 || isZero(*this)) {
		
		HugeInt temp(0);
		return temp;

	}

	HugeInt nObj(n);
	
	nObj.polarity = 0;
	
	HugeInt temp = *this * nObj;
	temp.polarity = (this->polarity ^ (n < 0));
	
	return temp;

}

HugeInt HugeInt::operator * (HugeInt& H) {


	
	if (isZero(*this) || isZero(H)) {
		
		HugeInt temp(0);
		return temp;

	}

	int aLen = this->length;
	int bLen = H.length;

	int carry = 0;
	int currValue = 0;
	int rowInd = 0, colInd = 0;

	int** rows = new int*[bLen];
	for (int i = 0; i < bLen; i++) {
	
		rows[i] = new int[aLen + 1];

		for (int j = 0; j < aLen + 1; j++) {
			
			rows[i][j] = 0;

		}

	}

	for (int i = bLen - 1, rowInd = 0; i >= 0; i--, rowInd++) {
	


		for (int j = aLen - 1, colInd = aLen; j >= 0; j--, colInd--) {

		

			currValue = carry + ((*this)[j] * H[i]);

			if (currValue > 9) {
			
				//cout << currValue % 10 << " ";

				rows[rowInd][colInd] = currValue % 10;

				carry = currValue / 10;

			} else {
				
				//cout << currValue << " ";

				rows[rowInd][colInd] = currValue;

				carry = 0;

			}

		}

		if (carry > 0) {

			// cout << carry << " ";
			rows[rowInd][colInd] = carry;
		
		}

		carry = 0;

	}

	int currSum = 0;
	carry = 0;

	int prodLen = bLen + aLen + 1;
	int* prod = new int[prodLen];

	for (int i = 0; i < prodLen; i++)
		prod[i] = 0;

	int k = 0;
	for (int i = aLen; i >= 0; i--) {
		
		
		currSum = 0;

		for (int j = 0; i + j <= aLen && j < bLen; j++) {
			

			//cout << rows[j][i + j] << " ";

			currSum += rows[j][i + j];

		}


		currSum += carry;

		//cout << "curr " << currSum << endl;


		if (currSum > 9) {
			
			carry = currSum / 10;
			prod[prodLen - 1 - k] = currSum % 10;

		} else {
			
			prod[prodLen - 1 - k] = currSum;
			carry = 0;

		}


		k++;

	}

	for (int i = 1; i < bLen; i++) {

		currSum = 0;
		
		for (int j = 0; i + j < bLen ; j++) {
		
			//cout << rows[i + j][j] << " ";
			currSum += rows[i + j][j];

		}

		currSum += carry;


		if (currSum > 9) {
			
			carry = currSum / 10;
			prod[prodLen - 1 - k] = currSum % 10;

		} else {
			
			prod[prodLen - 1 - k] = currSum;
			carry = 0;

		}


		k++;


	}

	// Clean Up

	for (int i = 0; i < prodLen && prod[i] == 0;) {
		
		while (prod[i] == 0) {
			
			for (int j = i; j < prodLen - 1; j++) {
				
				prod[j] = prod[j + 1];

			}

			prodLen--;

		}

		i = 0;

	}

	HugeInt tempObj;

	tempObj.rows = (int) ceil(prodLen/9.0);
	tempObj.ptr = new int [tempObj.rows];
	tempObj.polarity = (this->polarity ^ H.polarity);
	tempObj.length = prodLen;

	int numBuff = 0;

	for (int i = 0, rCount = 0; i < prodLen; i += 9, rCount++) {
			
		numBuff = 0;

		for (int j = prodLen - 1 - i, dCount = 0; j >= 0 && j >= prodLen - 9 - i; j--, dCount++) {
				
			numBuff += prod[j] * (int)pow(10, dCount);
		//	cout << "numBuff-> " << numBuff << endl;

		}

		//cout << "rCount-> " << rCount << endl;
		tempObj.ptr[rCount] = numBuff;

	}

	delete[] prod;

	return tempObj;



}

HugeInt HugeInt::operator - (const int n) {

	HugeInt nObj(n);

	HugeInt objA, objB;

	if (*this == nObj) {
	
		HugeInt temp(0);
		return temp;

	}

	objA = (*this > nObj) ? *this : nObj;
	objB = (*this < nObj) ? *this : nObj;

	HugeInt tempObj = objA - objB;
	tempObj.polarity = (objA != *this);

	return tempObj;


}

HugeInt HugeInt::operator - (HugeInt& H) {


	HugeInt objA, objB;

	if (*this == H) {
	
		HugeInt temp(0);
		return temp;

	}

	objA = (*this > H) ? *this : H;
	objB = (*this < H) ? *this : H;

	int aLen = objA.length;
	int bLen = objB.length;

	int currVal = 0, carry = 0;

	int tempLen = (aLen > bLen) ? aLen : bLen;
	int* temp = new int[tempLen];

	for (int i = 0; i < tempLen; i++) temp[i] = 0;

	for (int i = aLen - 1, j = bLen - 1, tempInd = tempLen - 1; i >= 0; i--, j--, tempInd--) {
		
		if (objA[i] < objB[j]) {
			
			currVal = (10 + objA[i]) - objB[j] - carry;
			carry = 1;

		} else {
			
			currVal = objA[i] - objB[j] - carry;
			carry = 0;

		}

		temp[tempInd] = currVal;

	}
/*
	for (int i = 0; i < tempLen; i++)
		cout << temp[i];

	cout << endl;*/


	for (int i = 0; i < tempLen && temp[i] == 0;) {
		
			while (temp[i] == 0) {
			
				for (int j = i; j < tempLen - 1; j++) {
				
					temp[j] = temp[j + 1];

				}

				tempLen--;

			}

			i = 0;

		}

		/*cout << "sum -> ";
		for (int i = 0; i < sumLen; i++)
			cout << temp[i];
		cout << endl;*/

		HugeInt tempObj;

		tempObj.rows = (int) ceil(tempLen/9.0);
		tempObj.ptr = new int [tempObj.rows];
		tempObj.polarity = (objA != *this);
		tempObj.length = tempLen;

		int numBuff = 0;

		for (int i = 0, rCount = 0; i < tempLen; i += 9, rCount++) {
			
			numBuff = 0;

			for (int j = tempLen - 1 - i, dCount = 0; j >= 0 && j >= tempLen - 9 - i; j--, dCount++) {
				
				//cout << "temp[j]" << temp[j] << endl;
				//cout << "j: " << j << endl;

				numBuff += temp[j] * (int)pow(10, dCount);
				//cout << "numBuff-> " << numBuff << endl;

			}

			//cout << "rCount-> " << rCount << endl;
			tempObj.ptr[rCount] = numBuff;
			//cout << "ptr[rCount]: " << tempObj.ptr[rCount] << endl;

		}

		/*cout << "sum -> ";
		for (int i = 0; i < sumLen; i++)
			cout << temp[i];
		cout << endl;*/

		delete[] temp;

		return tempObj;


}

HugeInt HugeInt::operator / (HugeInt& H) {
	
	HugeInt objA, objB;

	if (*this == H) {
	
		HugeInt temp(1);
		return temp;

	}

	if (isZero(*this)) return *this;
	if (isZero(H)) {
		
		cout << "Undefined! Illegal Operation!" << endl;
		
		system("pause");
		
		HugeInt temp(INT_MIN);

		return temp;

	}

	objA = (*this > H) ? *this : H; // bara number
	objB = (*this < H) ? *this : H; // chota number

	// 33792341235612341
	// 338

	int aLen = objA.length;
	int bLen = objB.length;

	int* bArr = new int[bLen];
	for (int i = 0; i < bLen; i++)
		bArr[i] = objB[i];

	int* buff = new int[bLen + 1];
	for (int i = 0; i <= bLen; i++)
		buff[i] = 0;
	int buffLen = 0;


		HugeInt tempObj(0);

		int i = 0;

		while (tempObj < objB) {
		
			tempObj = (tempObj * 10) + objA[i];

			i++;

		}

		HugeInt toBeSubtracted = objB;

		while (toBeSubtracted < tempObj) {

			toBeSubtracted = toBeSubtracted + objB;

		}

		toBeSubtracted = toBeSubtracted - objB;
	
		/*cout << ">>";
		cout << toBeSubtracted << endl;*/

		int* tbsArray = new int[aLen];

		for (i = 0; i < toBeSubtracted.length; i++) {
		
			tbsArray[i] = toBeSubtracted[i];

		}

		for (i = toBeSubtracted.length; i < aLen; i++) {
		
			tbsArray[i] = 0;

		}

		/*cout << "tbs-> " << endl;
		for (i = 0; i < aLen; i++) cout << tbsArray[i] << " ";
		cout << endl;*/

		HugeInt temp;

		temp.rows = (int) ceil(aLen/9.0);
		temp.ptr = new int [temp.rows];
		temp.polarity = 0;
		temp.length = aLen;

		int numBuff = 0;

		for (int i = 0, rCount = 0; i < aLen; i += 9, rCount++) {
			
			numBuff = 0;

			for (int j = aLen - 1 - i, dCount = 0; j >= 0 && j >= aLen - 9 - i; j--, dCount++) {
				
				numBuff += tbsArray[j] * (int)pow(10, dCount);
			//	cout << "numBuff-> " << numBuff << endl;

			}

			//cout << "rCount-> " << rCount << endl;
			temp.ptr[rCount] = numBuff;

		}

		delete[] tbsArray;

		cout << "temp->" << temp << endl;

		temp = objA - temp;
		objA = temp;

		cout << "objA ->";
		cout << objA << endl;

		if (objA < objB || isZero(objA)) return temp;

	return temp;

}

ostream& operator << (ostream& out, HugeInt& H) {

	(H.polarity == 1)? cout << "-" : cout << "+";
	for (int i = H.rows - 1; i >= 0; i--) {
		
		if (H.ptr[i] != 0) {

			for (int j = 0; j < abs(H.getNumLength(H.ptr[i]) - 9); j++)
				cout << "0";

			out << H.ptr[i] << " ";

		}
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

	for (int i = 0; i < H.rows; i++) H.ptr[i] = 0;

	if (buffLen == 0) {
		
		HugeInt temp(0);
		H = temp;

	}
	
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
