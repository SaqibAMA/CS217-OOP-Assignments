#include "HugeInt.h"

void* operator new (size_t size) {

	return malloc(size);

}

HugeInt::HugeInt() {

	ptr = new int(0);
	length = 0;
	polarity = 0;
	rows = 1;

}

HugeInt::HugeInt(int x) {
	
	ptr = new int(abs(x));
	length = getNumLength(x);
	polarity = (x < 0);
	rows = (int) ceil(length / 9.0);

}

HugeInt::HugeInt(const HugeInt& H) {

	this->length = H.length;
	this->polarity = H.polarity;
	this->rows = H.rows;
	
	this->ptr = new int[rows];
	for (int i = 0; i < rows; i++)
		this->ptr[i] = H.ptr[i];

}

HugeInt::HugeInt(int* A, int s, bool polarity, bool def = true) {
	if (def) {
		this->polarity = polarity;
		this->rows = s;
		this->length = 0;

		this->ptr = new int[this->rows];

		for (int i = 0; i < this->rows; i++) {
		
			this->ptr[i] = A[i];
		
			if (i < this->rows - 1) {
			
				this->length += 9;

			} else {
			
				this->length += getNumLength(A[i]);

			}

		}
	} else {
		
		this->polarity = polarity;
		this->length = s;
		this->rows = (int) ceil(length / 9.0);
		
		this->ptr = new int[this->rows];

		int numBuff = 0;

		for (int i = 0, rCount = 0; i < this->length; i += 9, rCount++) {
			
		numBuff = 0;

		for (int j = this->length - 1 - i, dCount = 0; j >= 0 && j >= this->length - 9 - i; j--, dCount++) {
				
			numBuff += A[j] * (int) pow(10, dCount);

		}

		this->ptr[rCount] = numBuff;

		}


	}

}

// Relational operators

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

	if ((this->length != H.length) ||
		(this->polarity != H.polarity)) {
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
	
	//cout << "length of *this -> " << this->length << endl;
	//cout << "length of H ->" << H.length << endl;

	if ((this->length > H.length) ||
		(this->polarity == 0 && H.polarity == 1)) return false;

	//cout << "Length verified!" << endl;

	if (this->length < H.length) return true;

	//cout << "Length verified again!" << endl;

	if (this->length == H.length) {
	
		for (int i = rows - 1; i >= 0; i--) {
		
			if (this->ptr[i] < H.ptr[i]) {

				//cout << "this->ptr[i] -> " << this->ptr[i] << endl;
				//cout << "H.ptr[i] -> " << H.ptr[i] << endl;
				//
				//cout << "row result-> ";
				//cout << (this->ptr[i] < H.ptr[i]) << endl;

				return true;

			} else if (this->ptr[i] != H.ptr[i]) {
				
				return false;

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


// Arithmetic

HugeInt HugeInt::operator + (const HugeInt& H) {

	if (!this->polarity && H.polarity) {
	
		HugeInt objA(*this), objB(H);

		bool polCache = (objB >= objA);

		objA.polarity = objB.polarity = 0;

		HugeInt temp = objA - objB;

		temp.polarity = polCache;

		return temp;

	}

	if (this->polarity && !H.polarity) {
	
		HugeInt objA(*this), objB(H);

		bool polCache = (objA >= objB);

		objA.polarity = objB.polarity = 0;

		HugeInt temp = objB - objA;

		temp.polarity = polCache;

		return temp;

	}

	if (!(this->polarity ^ H.polarity)) {

		if (isZero(*this)) return H;
		if (isZero(H)) return *this;
		
		
		int limit = (this->rows > H.rows) ? this -> rows : 
			H.rows;

		int opA = 0, opB = 0, carry = 0;
		int currSum = 0, sumLimit = 0;

		int* sum = new int[limit + 1];
		for (int i = 0; i < limit + 1; i++)
			sum[i] = 0;

		for (int i = 0; i < limit; i++) {
			
			opA = (i < this->rows) ? ptr[i] : 0;
			opB = (i < H.rows) ? H.ptr[i] : 0;

			currSum = carry + opA + opB;

			if (currSum >= 1000000000) {
				
				currSum -= 1000000000;
				carry = 1;

			} else {
			
				carry = 0;

			}

			sum[i] = currSum;
			sumLimit++;


		}

		if (carry) {
			
			if (sum[limit - 1] < 999999998 && 
				sum[limit - 1] != 0 && 
				sumLimit < limit) {

				sum[limit - 1] += carry;
				//sumLimit = limit;

			} else {
				
				sum[limit] += carry;
				sumLimit++;
				//sumLimit = limit + 1;

			}

		}

		HugeInt temp(sum, sumLimit, (this->polarity || H.polarity));
		
		delete[] sum;

		return temp;

	}

	HugeInt temp(0);
	return temp;

}

HugeInt HugeInt::operator + (const int n) {

	HugeInt nObj(n);

	return (*this + nObj);

}

HugeInt HugeInt::operator - (const HugeInt& H) {

	if (*this == H || (isZero(*this) && isZero(H))) {
		
		HugeInt temp(0);
		return temp;

	}

	if (isZero(*this)) {
		
		HugeInt temp(H);
		temp.polarity = 1;

		return temp;

	}

	if (isZero(H)) {
		
		HugeInt temp(*this);
		return temp;

	}

	if ((this->polarity == 1 && H.polarity == 1) ||
	(this->polarity && !H.polarity)){

		HugeInt objA(*this), objB(H);

		objA.polarity = objB.polarity = 0;

		HugeInt temp = objA + objB;

		temp.polarity = 1;

		return temp;

	}

	if (!this->polarity && H.polarity) {
	
		HugeInt objA(*this), objB(H);

		objA.polarity = objB.polarity = 0;

		HugeInt temp = objA + objB;

		return temp;

	}

	HugeInt objA = (*this > H) ? *this : H;
	HugeInt objB = (*this < H) ? *this : H;

	int limit = (objA.rows > objB.rows) ? 
		objA.rows : objB.rows;

	int carry = 0, opA = 0, opB = 0, currDiff = 0;

	int* diff = new int[limit];
	int diffLim = 0;

	for (int i = 0; i < limit; i++) {
		
		opA = (i < objA.rows) ? objA.ptr[i] : 0;
		opB = (i < objB.rows) ? objB.ptr[i] : 0;

		//cout << "opA->" << opA << endl;
		//cout << "opB->" << opB << endl;


		// added this opA == opB condition because the program
		// was getting a weird carry problem

		if (opA == opB) {
		
			if (carry) carry++;

			currDiff = opA - opB;

		}
		else if (opA > opB) {
			
			currDiff = opA - opB - carry;
			carry = 0; // potentially bad

		} else {
			
			currDiff = (1000000000 + opA) - opB - carry;
			carry = 1;

		}

		diff[i] = currDiff;
		diffLim++;

	}

	for (int i = diffLim - 1; i >= 0 && diff[i] == 0; i++)
		if (diff[i] == 0) diffLim--;

	HugeInt temp(diff, diffLim, (objA != *this));
	
	delete[] diff;

	return temp;


}

HugeInt HugeInt::operator - (const int n) {

	HugeInt nObj(n);

	return (*this - nObj);

}

HugeInt HugeInt::operator * (const HugeInt& H) {


	if (isZero(*this) || isZero(H)) {
	
		HugeInt temp(0);
		return temp;
			
	}

	if (this->rows < 2 && this->ptr[0] == 1) {
		
		return H;

	}

	if (H.rows < 2 && H.ptr[0] == 1) {
	
		return *this;

	}

	HugeInt objA(*this);
	HugeInt objB(H);


	int tempALen = 9 * objA.rows;
	int* tempA = new int[tempALen];

	for (int i = 0; i < tempALen; i++)
		tempA[i] = 0;

	for (int i = objA.rows - 1, dCount = 0; i >= 0; i--) {

		// agar koi masla ho tou check here
		// kiunke yahan pehle simple ptr use kia hua tha
		// bajaaye ke objA.ptr ke

		if (objA.ptr[i] != 0) {

			int offset = 9 - getNumLength(objA.ptr[i]);
			//cout << "offset-> " << offset << endl;
			//cout << "objA.ptr[i]-> " << objA.ptr[i] << endl;

			int num = objA.ptr[i];
			int numInd = getNumLength(objA.ptr[i]);

			for (int j = dCount + offset;
				j < dCount + offset + getNumLength(objA.ptr[i]) &&
				j < tempALen;
				j++) {
			
					tempA[j] = (int)((double) num / pow(10, numInd - 1)) % 10;
					numInd--;

			}

		}

		dCount += 9;

	}



	int tempBLen = 9 * objB.rows;
	int* tempB = new int[tempBLen];


	for (int i = 0; i < tempBLen; i++)
		tempB[i] = 0;

	for (int i = objB.rows - 1, dCount = 0; i >= 0; i--) {


		if (objB.ptr[i] != 0) {

			int offset = 9 - getNumLength(objB.ptr[i]);
			//cout << "offset-> " << offset << endl;
			//cout << "objA.ptr[i]-> " << objA.ptr[i] << endl;

			int num = objB.ptr[i];
			int numInd = getNumLength(objB.ptr[i]);

			for (int j = dCount + offset;
				j < dCount + offset + getNumLength(objB.ptr[i]) &&
				j < tempBLen;
				j++) {
			
					tempB[j] = (int)((double) num / pow(10, numInd - 1)) % 10;
					numInd--;

			}

		}

		dCount += 9;

	}


	int** prodRows = new int*[tempBLen];

	int rowLen = tempALen + tempBLen + 1;

	for (int i = 0; i < tempBLen; i++) {
	
		prodRows[i] = new int[rowLen];

		for (int j = 0; j < rowLen; j++) {
		
			prodRows[i][j] = 0;

		}

	}


	//// Mutliplication Algo

	int carry = 0, opA = 0, opB = 0;
	int currValue = 0, offset = 0;

	for (int i = tempBLen - 1, offset = 0; i >= 0; i--, offset++) {
	
		opA = tempB[i];
		int dCount = rowLen - 1;

		for (int j = tempALen - 1; j >= 0; j--, dCount--) {
			
			opB = tempA[j];

			currValue = (opA * opB) + carry;

			if (currValue > 9) {
				
				prodRows[offset][dCount - offset] = currValue % 10;
				carry = currValue / 10;

			} else {
				
				prodRows[offset][dCount - offset] = currValue;
				carry = 0;

			}

		}

		if (carry) {
		
			prodRows[offset][dCount - offset] = carry;

		}

	}



	int prodLen = rowLen;
	int* prod = new int[rowLen];

	int currSum = 0;
	carry = 0;

	for (int i = prodLen - 1; i >= 0; i--) {
	
		currSum = 0;

		for (int j = 0; j < tempBLen; j++) {
			
			currSum += prodRows[j][i];

		}

		currSum += carry;

		if (currSum > 9) {
			
			prod[i] = currSum % 10;
			carry = currSum / 10;

		} else {
			
			prod[i] = currSum;
			carry = 0;

		}

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


	delete[] tempA;
	delete[] tempB;
	free(prodRows);

	HugeInt temp(prod, prodLen, (this->polarity ^ H.polarity), false);

	delete[] prod;

	return temp;
}

HugeInt HugeInt::operator * (const int n) {
	
	HugeInt nObj(n);

	return (*this * nObj);

}


HugeInt HugeInt::operator / (const HugeInt& H) {

	
	HugeInt objA(*this);	// Dividend
	HugeInt objB(H);		// Divisor

	//					-------------------
	//	25 (divisor)	|	12345 (dividend)


	if (H.rows < 2 && H.ptr[0] == 1) return *this;
	if (isZero(objA)) {
		
		HugeInt temp(0);
		return temp;

	}
	if (isZero(objB)) {
		
		cout << "Undefined!" << endl;
		HugeInt temp(0);
		return temp;

	}


	HugeInt dvdBuff(0);
	HugeInt result(0);

	/*
	
	~Remarks

	Deal with cases where there are only single
	row integers.

	i.e. 1324 & 21313465;

	*/


	/*
	
	Finding a portion of objA that
	is sufficient enough to be 
	divided by ObjB.

	*/

	int currRow = objA.rows - 1;
	int dCount = 0, digitsLeft = objA.length;

	bool zeroRow = false;


	while (dvdBuff < objB) {
	
	
		dvdBuff = dvdBuff * 10;

		int num = objA.ptr[currRow];

		if (num > 0) {

			int digit = 0;
		
			if (num >= 99999999 && currRow != objA.rows - 1) {

				if (getNumLength(num) - dCount - 1 >= 0)
					digit = int(num / pow(10, getNumLength(num) - dCount - 1))
					% 10;
				else
					digit = int(num / pow(10, getNumLength(num) - dCount))
					% 10;



			} else if (num <= 99999999 && currRow != objA.rows - 1) {
			
				digit = int(num / pow(10, getNumLength(1000000000 + num) - dCount - 1)) % 10;


			} else if (currRow == objA.rows - 1) {
			
				digit = int(num / pow(10, getNumLength(num) - dCount - 1))
					% 10;

			}

			dCount++;

			dvdBuff = dvdBuff + digit;

			if (dCount == getNumLength(num) && currRow == objA.rows - 1) {
			
				currRow--;
				dCount = 0;

			}

			if (dCount == 10) {
			
				currRow--;
				dCount = 0;

			}

		} else if (num == 0) {
		
				if (!zeroRow) {
			
					dCount = 0;
					zeroRow = true;

				}

				dCount++;

				if (zeroRow && dCount == 10) {
			
					zeroRow = false;
					dCount = 0;
					currRow--;

				}


			}


	}

	digitsLeft -= dvdBuff.length;

	
	/*
	
	Finding a quotient big enough to
	divide dvdBuff. Quotient is "i".
	The value that can be subtracted from
	dvdBuff is divBuff.

	*/

	while (objA - (result * objB) > objB && digitsLeft >= 0) {

		cout << "dCount at the start of the loop->" << dCount << endl;

		HugeInt divBuff(objB);

		int i = 1;

		while (divBuff < dvdBuff) {
		
			divBuff = objB * i;
			i++;

		}

		if (i > 1) i--;
		if (divBuff != dvdBuff && divBuff > dvdBuff) {
		
			i--;
			divBuff = divBuff - objB;

		}

		cout << "bigEnoughNum is-> " << divBuff << endl;
		cout << "dvdBuff->" << dvdBuff << endl;
		cout << "quotient->" << i << endl;

		if (i > 0) {
		
			cout << "current Row->" << objA.ptr[currRow] << endl;


			dvdBuff = dvdBuff - divBuff;

			result = (result * 10) + i;


			dvdBuff = dvdBuff * 10;

			int num = objA.ptr[currRow];

			if (num > 0) {

				int digit = 0;
		
					if (num > 99999999 && currRow != objA.rows - 1) {

						if (getNumLength(num) - dCount - 1 >= 0)
							digit = int(num 
							/ pow(10, getNumLength(num) - dCount - 1))
							% 10;
						else
							digit = int(num 
							/ pow(10, getNumLength(num) - dCount))
							% 10;



					} else if (num <= 99999999 
						&& currRow != objA.rows - 1) {
			
							if (dCount >= 9 - getNumLength(num)) {
								digit = int(num
							/ pow(10, getNumLength(1000000000 + num)
							- dCount + 2)) % 10;
							}


					} else if (currRow == objA.rows - 1) {
			
						digit = int(num 
							/ pow(10, getNumLength(num) - dCount - 1))
							% 10;

					}

					dCount++;
					digitsLeft--;

					dvdBuff = dvdBuff + digit;

					if (dCount == getNumLength(num) 
						&& currRow == objA.rows - 1) {
			
						currRow--;
						dCount = 0;

					}

					if (dCount == 10) {
			
						currRow--;
						dCount = 0;

					}


				} else if (num == 0) {
		
					if (!zeroRow) {
						dCount = 0;
						zeroRow = true;
					}
					dCount++;
					digitsLeft--;

					if (zeroRow && dCount == 10) {
						zeroRow = false;
						dCount = 0;
						currRow--;
					}

			
				}



		} else if (i == 0) {

			while (dvdBuff < objB && digitsLeft > 0) {


				result = result * 10;

				dvdBuff = dvdBuff * 10;



				int num = objA.ptr[currRow];


				// bringing down a number
				if (num > 0) {

					int digit = 0;
		
						if (num > 99999999 && currRow != objA.rows - 1) {

							if (getNumLength(num) - dCount - 1 >= 0)
								digit = int(num 
								/ pow(10, getNumLength(num) - dCount - 1))
								% 10;
							else
								digit = int(num 
								/ pow(10, getNumLength(num) - dCount))
								% 10;



						} else if (num <= 99999999 
							&& currRow != objA.rows - 1) {
			
							digit = int(num
							/ pow(10, getNumLength(1000000000 + num)
							- dCount - 2)) % 10;


						} else if (currRow == objA.rows - 1) {
			
							digit = int(num 
								/ pow(10, getNumLength(num) - dCount - 1))
								% 10;

						}

						dCount++;
						digitsLeft--;

						dvdBuff = dvdBuff + digit;

						if (dCount == getNumLength(num) 
							&& currRow == objA.rows - 1) {
			
							currRow--;
							dCount = 0;

						}

						if (dCount == 10) {
			
							currRow--;
							dCount = 0;

						}


				} else if (num == 0) {
		
					if (!zeroRow) {
						dCount = 0;
						zeroRow = true;
					}
					dCount++;
					digitsLeft--;

					if (zeroRow && dCount == 10) {
						zeroRow = false;
						dCount = 0;
						currRow--;
					}

				}

			}

			if (isZero(dvdBuff)) {
				
				result = (result * 10);

			}

		}

		cout << "result ------>" << result << endl;

	}




	return result;


}


// Helper functions

bool HugeInt::isZero(const HugeInt& H) {

	return (H.rows < 2 && H.ptr[0] == 0);

}

int HugeInt::getNumLength(const int n) const {

	int len = 1;

	int _n = abs(n);

	while (_n > 9) {
		
		_n /= 10;
		++len;

	}

	return len;

}

bool HugeInt::isArrayGreater(int* A, int As, int* B, int Bs) {
	
	if (As < Bs) return false;
	if (As > Bs) return true;

	for (int i = 0; i < As; i++) {
		
		if (A[i] < B[i]) return false;

	}

	return true;

}


// Stream insertion and extraction

ostream& operator << (ostream& out, const HugeInt& H) {

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

	if (buffLen <= 0) {
		
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

// Destructors

HugeInt::~HugeInt() {

	delete[] ptr;
	length = 0;
	rows = 0;
	polarity = 0;

}
