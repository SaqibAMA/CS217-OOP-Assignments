#include "ticTacToe.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>

using namespace std;

extern void gotoxy(int x, int y);

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

ticTacToe::ticTacToe() {
	
	n = 3;

	board = new int*[n];
	for (int i = 0; i < n; i++) {
		
		board[i] = new int[n];

		for (int j = 0; j < n; j++){
			board[i][j] = 0;
		}

	}

	board[2][1] = -1;
	board[1][1] = 1;

	boardState = 0;

}

ticTacToe::ticTacToe(int _n) {
	
	n = _n;

	board = new int*[n];
	for (int i = 0; i < n; i++) {
		
		board[i] = new int[n];

		for (int j = 0; j < n; j++){
			board[i][j] = 0;
		}

	}

	boardState = 0;

}



bool ticTacToe::isWon() {

	bool gameWonH = true;
	bool gameWonV = true;
	bool gameWonD = true;

	for (int i = 0; i < n; i++) {

		// Checking horizontal
		gameWonH = true;

		for (int j = 0; j < n - 1 && gameWonH; j++) {

			(board[i][j] == 0) ? gameWonH = false : gameWonH = !(board[i][j] != board[i][j + 1]);

		}

		if (gameWonH) return gameWonH;


		// Checking vertical
		gameWonV = true;

		for (int j = 0; j < n - 1 && gameWonV; j++) {
			
			(board[j][i] == 0) ? gameWonV = false : gameWonV = !(board[j][i] != board[j + 1][i]);

		}

		if (gameWonV) return gameWonV;

	}

	// Checking diagonal (right to left)
	gameWonD = true;

	for (int j = 0; j < n - 1 && gameWonD; j++) {
			
		(board[j][j] == 0) ? gameWonD = false : gameWonD = !(board[j][j] != board[j + 1][j + 1]);

	}

	if (gameWonD) return gameWonD;


	// Checking diagonal (left to right)
	gameWonD = true;

	for (int i = n - 1, j = 0; i > 0 && gameWonD; i--, j++) {

		(board[j][i] == 0) ? gameWonD = false : gameWonD = !(board[j][i] != board[j + 1][i - 1]);

	}

	if (gameWonD) return gameWonD;


	return false;

}

void ticTacToe::print(){

	char buff;
	int w = 30;	// width of the grid

	int yAlign = 10;

	//for (int j = 0; j < w; j++) cout << "-";
	cout << endl;

	SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
	
	for (int j = 0; j < n; j++) {
		gotoxy(yAlign + (j*10), 8);
		cout << setw(5) << " " << setw(5) << " ";
	}
	cout << endl;

	for (int i = 0, rowCount = 9; i < n; i++, rowCount += 2) {

		for (int j = 0; j < n; j++) {

			gotoxy(yAlign + (j*10), rowCount);

			if (board[i][j] == 0) {
				buff = '-';
				SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			}
			else if (board[i][j] == -1) {
				buff = 'O';
				SetConsoleTextAttribute(h, 2 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			}
			else {
				buff = 'X';
				SetConsoleTextAttribute(h, 4 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
			}

			cout << setw(5) << buff << setw(5) << " ";

		}

		cout << endl;
		SetConsoleTextAttribute(h, 0 | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
		for (int j = 0; j < n; j++) {
			gotoxy(yAlign + (j*10), rowCount + 1);
			cout << setw(5) << " " << setw(5) << " ";
		}
		SetConsoleTextAttribute(h, 15);
		cout << endl;

	}

}

ticTacToe::~ticTacToe() {

	for (int i = 0; i < n; i++){
		delete[] board[i];
	}
	board = nullptr;

}
