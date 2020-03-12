#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include "ticTacToe.h"

using namespace std;

HANDLE hM = GetStdHandle(STD_OUTPUT_HANDLE);

void gotoxy(int x, int y) {
	
	COORD scrn;
	scrn.X = x;
	scrn.Y = y;

	SetConsoleCursorPosition(hM, scrn);

}

int getChoice(){

	int choice = 1;

	int yAlign = 40;

	SetConsoleTextAttribute(hM, 15 | BACKGROUND_GREEN | BACKGROUND_BLUE);

	gotoxy(yAlign, 5);
	cout << setw(5) << "                                 " << endl;
	gotoxy(yAlign, 6);
	cout << setw(5) << " " << setw(5) << "      TIC TAC TOE      " << setw(5) << " " << endl;
	gotoxy(yAlign, 7);
	cout << setw(5) << "                                 " << endl;
	gotoxy(yAlign, 8);
	cout << setw(5) << " " << setw(5) << "     BY  SAQIB ALI     " << setw(5) << " " << endl;
	gotoxy(yAlign, 9);
	cout << setw(5) << "                                 " << endl;

	SetConsoleTextAttribute(hM, 15 | BACKGROUND_BLUE);

	gotoxy(yAlign, 11);
	cout << setw(5) << "                                 " << endl;
	gotoxy(yAlign, 12);
	cout << setw(5) << " " << setw(5) << "-> SIMPLE TIC TAC TOE  " << setw(5) << " " << endl;
	gotoxy(yAlign, 13);
	cout << setw(5) << "                                 " << endl;

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);

	gotoxy(yAlign, 14);
	cout << setw(5) << "                                 " << endl;
	gotoxy(yAlign, 15);
	cout << setw(5) << " " << setw(5) << " ULTIMATE TIC TAC TOE  " << setw(5) << " " << endl;
	gotoxy(yAlign, 16);
	cout << setw(5) << "                                 " << endl;
	SetConsoleTextAttribute(hM, 15);

	gotoxy(yAlign, 18);
	cout << setw(5) << "*********************************" << endl;

	while (true) {

		if (GetAsyncKeyState(VK_DOWN) & 0x28000) {

			Sleep(100);

			gotoxy(0, 0);

			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			gotoxy(yAlign, 11);
			cout << setw(5) << "                                 " << endl;
			gotoxy(yAlign, 12);
			cout << setw(5) << " " << setw(5) << "  SIMPLE TIC TAC TOE   " << setw(5) << " " << endl;
			gotoxy(yAlign, 13);
			cout << setw(5) << "                                 " << endl;

			SetConsoleTextAttribute(hM, 15 | BACKGROUND_BLUE);
			gotoxy(yAlign, 14);
			cout << setw(5) << "                                 " << endl;
			gotoxy(yAlign, 15);
			cout << setw(5) << " " << setw(5) << "-> ULTIMATE TIC TAC TOE" << setw(5) << " " << endl;
			gotoxy(yAlign, 16);
			cout << setw(5) << "                                 " << endl;

			choice = 2;

			
			
		} else if (GetAsyncKeyState(VK_UP) & 0x26000){
			
			Sleep(100);

			gotoxy(0, 0);

			SetConsoleTextAttribute(hM, 15 | BACKGROUND_BLUE);
			gotoxy(yAlign, 11);
			cout << setw(5) << "                                 " << endl;
			gotoxy(yAlign, 12);
			cout << setw(5) << " " << setw(5) << "-> SIMPLE TIC TAC TOE  " << setw(5) << " " << endl;
			gotoxy(yAlign, 13);
			cout << setw(5) << "                                 " << endl;

			SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			gotoxy(yAlign, 14);
			cout << setw(5) << "                                 " << endl;
			gotoxy(yAlign, 15);
			cout << setw(5) << " " << setw(5) << " ULTIMATE TIC TAC TOE  " << setw(5) << " " << endl;
			gotoxy(yAlign, 16);
			cout << setw(5) << "                                 " << endl;

			choice = 1;

		} else if (GetAsyncKeyState(VK_RETURN) & 0x0D000) {
			
			Sleep(100);
			return choice;

		}

		SetConsoleTextAttribute(hM, 15);

	}

	return choice;
}

int getBoardSize() {
	
	int yAlign = 40;
	int n = 3;

	SetConsoleTextAttribute(hM, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);

	gotoxy(yAlign, 5);
	cout << setw(5) << "                                 " << endl;

	gotoxy(yAlign, 6);
	cout << setw(5) << "   ENTER THE SIZE OF THE BOARD   " << endl;

	gotoxy(yAlign, 7);
	cout << setw(5) << "                                 ";
	
	gotoxy(yAlign, 8);
	cout << setw(5) << "          LEFT / RIGHT           ";

	gotoxy(yAlign, 9);
	cout << setw(5) << "                                 ";

	gotoxy(yAlign, 10);
	cout << setw(5) << " <<                           >> ";

	gotoxy(yAlign, 11);
	cout << setw(5) << "                                 ";

	gotoxy(yAlign + 16, 10);
	cout << n << endl;

	while (true) {

		if (GetAsyncKeyState(VK_RIGHT) & 0x27) {
			

			//SetConsoleTextAttribute(hM, 15);
			SetConsoleTextAttribute(hM, 3 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			gotoxy(yAlign + 14, 10);
			cout << "      " << endl;

			n++;

			gotoxy(yAlign + 16, 10);
			cout << n << endl;

			Sleep(100);

		} else if (GetAsyncKeyState(VK_LEFT) & 0x25) {
			
			if (n > 3) {
				SetConsoleTextAttribute(hM, 3 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
				gotoxy(yAlign + 14, 10);
				cout << "      " << endl;

				n--;

				gotoxy(yAlign + 16, 10);
				cout << n << endl;

				Sleep(100);
			}

		} else if (GetKeyState(VK_RETURN) & 0x0D) {
		
			SetConsoleTextAttribute(hM, 15);
			Sleep(100);
			return n;

		}

	}

	cout << endl;

	return n;
}

int main(){

	int mode = getChoice();

	system("cls");

	if (mode == 1) {
		
		int n = getBoardSize();
		
		ticTacToe game(n);

		system("cls");

		game.print();

	}

	return 0;
}