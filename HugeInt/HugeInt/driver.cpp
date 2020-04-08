#include <iostream>
#include "HugeInt.h"

using namespace std;

int main(){

	HugeInt h1(2);
	HugeInt h2(5);

	cout << "enter h1->";
	cin >> h1;

	cout << "enter h2->";
	cin >> h2;

	// 1000000000000000000000000100
	// 0000000000000000009999999999
	// 1 000000000 000000000 000000100
	// 1 000000000 000000000 000000105

	cout << (h1 * h2) << endl;
	

	// implement polarity cache for
	// subtraction

	return 0;
}