#include <iostream>
#include <ctime>
#include "MyString.h"
#include "HugeInt.h"

using namespace std;

int main() {


	MyString str1("Saqib"), str2("Ali");


	cout << "concatenate->" << endl;
	cout << (str1 + str2) << endl;


	return 0;
}