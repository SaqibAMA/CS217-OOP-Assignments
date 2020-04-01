#include <iostream>
#include "MyString.h"
#include "HugeInt.h"

using namespace std;

int main() {

	//54136543 643643541 63413643(5) 443541634
	//5413654364364354163413643544354163

	HugeInt h1(123456);

	HugeInt h2(h1);

	HugeInt h3(-4568898);


	h1 = h3;

	cin >> h1;

	h3 = h1;

	cout << h3 << endl;

	cout << h1 << endl;
	
	return 0;
}