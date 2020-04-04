#include <iostream>
#include <ctime>
#include "MyString.h"
#include "HugeInt.h"

using namespace std;

int main() {

	//54136543 643643541 63413643(5) 443541634
	//5413654364364354163413643544354163

	// 333179521389983125971113233711

	HugeInt h1(999999999);

	HugeInt h3(999999999);

	HugeInt h2(h1);

	clock_t t = clock();
	cout << "Started..." << endl;

	cout << (h1 * 999999) << endl;
	
	double time = (clock() - t) / 1000;

	cout << "\nTime: " << (double) time << " seconds" << endl;

	return 0;
}