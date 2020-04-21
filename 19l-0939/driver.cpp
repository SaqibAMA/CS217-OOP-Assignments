#include <iostream>
#include "MyString.h"

using namespace std;

int main() {

	

	MyString str;
	cin >> str;


	cout << str;
	str[0] = 'h';
	MyString str1(str);

	str1 = str + "def";


	str1 = str + str;
	
	MyString str2 = str1 - "cd";

	MyString str4 ("Hello abcdef");
	
	str = str4 - str1;
	
	ifstream fin;
	fin.open("myfile.txt");
	fin>>str1>>str2;
	fin.close();

	MyString str3("Saqib");

	ofstream fout;
	fout.open("output.txt");
	fout << str1 << str2 << str3 + str4;

	ofstream object;
	fout.close();



	return 0;
}