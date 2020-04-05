#include <iostream>
#include <ctime>
#include "MyString.h"
#include "HugeInt.h"

using namespace std;

int main() {

	//54136543 643643541 63413643(5) 443541634
	//5413654364364354163413643544354163

	// 333179521389983125971113233711

	HugeInt h1, h2;

	cin >> h1;
	cin >> h2;


	cout << (h1 * h2) << endl;


	return 0;
}