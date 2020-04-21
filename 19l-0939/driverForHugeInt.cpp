
#include <iostream>
#include <Windows.h>


#include "HugeInt.h"

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y) {
	
	COORD scrn;
	scrn.X = x;
	scrn.Y = y;

	SetConsoleCursorPosition(h, scrn);

}

int main(){


	HugeInt h1(0), h2(0);
	char op[3];

	SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

	for (int i = 9; i < 28; i++) {
		
		gotoxy(5, i);
		cout << "                                                                     " << endl;


	}
	
	SetConsoleTextAttribute(h, 5 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	gotoxy(30, 10);
	cout << " -> OPERATORS" << endl;
	SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	gotoxy(30, 13);
	cout << " -> ADDITION ( + )" << endl;
	gotoxy(30, 14);
	cout << " -> SUBTRACTION ( - )" << endl;
	gotoxy(30, 15);
	cout << " -> MULTIPLICATION ( * )" << endl;
	gotoxy(30, 16);
	cout << " -> DIVISION ( / )" << endl;
	


	SetConsoleTextAttribute(h, 5 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	gotoxy(30, 20);
	cout << " -> RELATIONAL" << endl;
	SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

	gotoxy(30, 22);
	cout << " -> LESS THAN & EQUAL TO ( < & <= )" << endl;
	gotoxy(30, 23);
	cout << " -> GREATER THAN & EQUAL TO ( < & <= )" << endl;
	gotoxy(30, 24);
	cout << " -> EQUAL TO ( == )" << endl;
	gotoxy(30, 25);
	cout << " -> NOT EQUAL TO ( != )" << endl;


	SetConsoleTextAttribute(h, 5 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	gotoxy(6, 10);
	cout << " -> FORMAT" << endl;
	SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
	
	gotoxy(6, 13);
	cout << " -> HUGE INT" << endl;
	gotoxy(6, 14);
	cout << " -> OPERATOR" << endl;
	gotoxy(6, 15);
	cout << " -> HUGE INT" << endl;



	while (true) {

		for (int i = 0; i <= 7; i++) {
		
			gotoxy(5, i);
			cout << "                                                                     " << endl;

		}


		SetConsoleTextAttribute(h, 5 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		gotoxy(30, 1);
		cout << "--HUGEINT CALCULATOR--" << endl;
		SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);

		gotoxy(6, 2);
		cin >> h1;

		gotoxy(6, 3);
		cin.getline(op,3);

		gotoxy(6, 4);
		cin >> h2;

		if (op[0] == '+') {
			
			gotoxy(6, 6);
			cout << h1 + h2 << endl;

		}
		
		if (op[0] == '-') {
			
			gotoxy(6, 6);
			cout << h1 - h2 << endl;

		}

		if (op[0] == '/') {
			
			gotoxy(6, 6);
			cout << h1 / h2 << endl;

		}

		if (op[0] == '*') {
			
			gotoxy(6, 6);
			cout << h1 * h2 << endl;

		}

		if (op[0] == '=') {
			
			if (op[1] == '=') {
				
				gotoxy(6, 6);
				(h1 == h2) ? cout << "Yes!" << endl : cout << "No!" << endl;

			} else if (op[1] == '\0') {
				
				h1 = h2;
				gotoxy(6, 6);
				cout << "A = B = " << h1 << endl;

			}

		}

		if (op[0] == '!' && op[1] == '=') {
			
			gotoxy(6, 6);
			(h1 != h2) ? cout << "Yes!" << endl : cout << "No!" << endl;

		}

		if (op[0] == '<') {
			
			if (op[1] == '=') {
				
				gotoxy(6, 6);
				(h1 <= h2) ? cout << "Yes!" << endl : cout << "No!" << endl;

			} else if (op[1] == '\0') {
				
				gotoxy(6, 6);
				(h1 < h2) ? cout << "Yes!" << endl : cout << "No!" << endl;

			}

		}

		if (op[0] == '>') {
			
			if (op[1] == '=') {
				
				gotoxy(6, 6);
				(h1 >= h2) ? cout << "Yes!" << endl : cout << "No!" << endl;

			} else if (op[1] == '\0') {
				
				gotoxy(6, 6);
				(h1 > h2) ? cout << "Yes!" << endl : cout << "No!" << endl;

			}

		}

		cin.get();
	
	}

	return 0;
}