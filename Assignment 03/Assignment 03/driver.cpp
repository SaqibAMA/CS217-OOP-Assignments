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

	cout << "Enter Int: ";
	cin >> h1;

	cout << "Enter Int2: ";
	cin >> h2;

	cout << "h1-> " << h1 << endl;

	/*int n;
	cout << "enter n->";
	cin >> n;*/

	// 1000000000000014000000000000
	// 123

	cout << (h1 * h2) << endl;


	return 0;
}