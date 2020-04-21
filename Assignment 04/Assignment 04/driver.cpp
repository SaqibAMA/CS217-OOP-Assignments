#include <iostream>
#include "Name.h"
#include "Date.h"
#include "mTime.h"
#include "Person.h"

using namespace std;

int main(){

	Name usrName("Saqib", "Ali");
	Date DOB(8, 10, 1999);

	Person p1(usrName, DOB, 20, 1);

	cout << p1 << endl;

	cin >> p1;

	cout << p1 << endl;

	return 0;
}