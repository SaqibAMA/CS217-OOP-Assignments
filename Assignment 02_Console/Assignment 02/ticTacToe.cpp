#include "ticTacToe.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <fstream>

using namespace std;

// Function to place the cursor on a certain
// coordinate
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

	boardState = -2;
	turn = 0;
	mvCount = 0;

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

	boardState = -2;
	turn = 0;
	mvCount = 0;

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

bool ticTacToe::isDraw() {
	
	return (boardState == 0);

}

void ticTacToe::print(){

	char buff;
	int w = 30;	// width of the grid

	int yAlign = 10;

	
	// Statistics section
	gotoxy(yAlign, 1);
	cout << " -> CURRENT TURN  ";
	gotoxy(yAlign, 2);
	(turn == 0)? cout << " -> X " << endl : cout << " -> O " << endl;


	// Instructions section

	gotoxy(yAlign + 45, 1);
	cout << "INSTRUCTIONS" << endl;
	gotoxy(yAlign + 45, 3);
	cout << "-> PRESS \"S\" TO SAVE          -> USE SPACE TO SELECT ROW" << endl;
	gotoxy(yAlign + 45, 4);
	cout << "-> PRESS \"L\" TO LOAD          -> USE ARROW KEYS TO TOGGLE" << endl;

	
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

			}
			else if (board[i][j] == -1) {
				buff = 'O';
			}
			else {
				buff = 'X';
			}

			cout << setw(5) << buff << setw(5) << " ";

		}

		cout << endl;
		for (int j = 0; j < n; j++) {
			gotoxy(yAlign + (j*10), rowCount + 1);
			cout << setw(5) << " " << setw(5) << " ";
		}
		(h, 15);
		cout << endl;

	}

}

void ticTacToe::saveGame() {
	
	ofstream fout;
	fout.open("Game.txt");

	fout << n << endl;

	fout << turn << endl;

	fout << boardState << endl;

	fout << mvCount << endl;

	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
			
			fout << board[i][j] << " ";

		}

		fout << endl;

	}

	
	gotoxy(55, 6);
	cout << "-> GAME SAVED!" << endl;
	Sleep(1000);
	SetConsoleTextAttribute(h, 0);
	gotoxy(55, 6);
	cout << "-> GAME SAVED!" << endl;
	SetConsoleTextAttribute(h, 15);


	fout.close();

}

void ticTacToe::loadGame() {

	ifstream fin;
	fin.open("Game.txt");

	if (fin) {

		int tempN;

		fin >> tempN;
		fin.ignore();

		if (tempN != n) {
			
			for (int i = 0; i < n; i++)
				delete[] board[i];

			board = new int*[tempN];
			for (int i = 0; i < tempN; i++)
				board[i] = new int[tempN];

			n = tempN;

			system("cls");

		}

		fin >> turn;
		fin.ignore();

		fin >> boardState;
		fin.ignore();

		fin >> mvCount;
		fin.ignore();

		for (int i = 0; i < n; i++) {
			
			for (int j = 0; j < n; j++) {
				
				fin >> board[i][j];

			}

			fin.ignore();

		}

		print();


		gotoxy(55, 6);
		cout << "-> GAME LOADED!" << endl;
		Sleep(1000);
		SetConsoleTextAttribute(h, 0);
		gotoxy(55, 6);
		cout << "-> GAME LOADED!" << endl;

		SetConsoleTextAttribute(h, 15);

	} else {
		
	}

}

int ticTacToe::getRow() {

	int row = 0;
	
	int yAlign = 5;


	gotoxy(yAlign, row + 9);
	cout << "-> " << endl;


	while (true) {
		
		if (row > 0 && (GetAsyncKeyState(VK_UP) & 0x26000)) {

			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign, row*2 + 9);
			cout << "-> " << endl;

			SetConsoleTextAttribute(h, 15);
			row--;
			gotoxy(yAlign, row*2 + 9);
			cout << "-> " << endl;

		} else if (row < n - 1 && (GetAsyncKeyState(VK_DOWN) & 0x28000)) {

			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign, row*2 + 9);
			cout << "-> " << endl;

			SetConsoleTextAttribute(h, 15);
			row++;
			gotoxy(yAlign, row*2 + 9);
			cout << "-> " << endl;

		} else if (GetAsyncKeyState(VK_SPACE) & 0x20000) {
			
			Sleep(200);
			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign, row*2 + 9);
			cout << "-> " << endl;
			SetConsoleTextAttribute(h, 15);


			return row;

		} else if (GetAsyncKeyState(0x53) & 0x53000) {
			
			Sleep(200);
			saveGame();

		} else if (GetAsyncKeyState(0x4C) & 0x4C000) {
			
			Sleep(200);
			loadGame();

		}

	}

	return row;
}

int ticTacToe::getCol() {


	int col = 0;
	
	int yAlign = 13;


	gotoxy(yAlign + col, 9 + (2 * n));
	cout << " ^ " << endl;

	
	while (true) {
		
		if (col > 0 && (GetAsyncKeyState(VK_LEFT) & 0x25000)) {

			Sleep(200);
			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + col * 10, 9 + (2 * n));
			cout << " ^ " << endl;

			SetConsoleTextAttribute(h, 15);
			col--;
			gotoxy(yAlign + col * 10, 9 + (2 * n));
			cout << " ^ " << endl;

		} else if (col < n - 1 && (GetAsyncKeyState(VK_RIGHT) & 0x27000)) {

			Sleep(200);
			
			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + col * 10, 9 + (2 * n));
			cout << " ^ " << endl;

			SetConsoleTextAttribute(h, 15);
			col++;
			gotoxy(yAlign + col * 10, 9 + (2 * n));
			cout << " ^ " << endl;

		} else if (GetAsyncKeyState(VK_SPACE) & 0x20000) {
			
			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + col * 10, 9 + (2 * n));
			cout << " ^ " << endl;
			SetConsoleTextAttribute(h, 15);

			Sleep(200);
			return col;

		} else if (GetAsyncKeyState(0x53) & 0x53000) {
			
			Sleep(200);
			saveGame();

		} else if (GetAsyncKeyState(0x4C) & 0x4C000) {
			
			Sleep(200);
			loadGame();

		}

	}
	
	return col;

}

int** ticTacToe::getBoard() {
	
	return board;

}

int ticTacToe::getBoardState() {

	if (isWon() && boardState == -2) {

		(turn == 0) ? boardState = 1 : boardState = -1;

	}

	if (boardState == -2 && mvCount == pow(n, 2)) {
		boardState = 0;
	}

	return boardState;

}

void ticTacToe::setTurn(int t) {
	
	turn = t;

}

bool ticTacToe::canMove(int i, int j) {
	
	if (board[i][j] != 0 || i >= n || i < 0 || j >= n || j < 0) return false;

	return true;

}

void ticTacToe::makeMove(int i, int j, bool u) {

	int yAlign = 10;

	if (boardState == -2 && !u) {
	
		if (canMove(i, j)) {

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign, 4);
			cout << " -> INVALID MOVE!" << endl;
			SetConsoleTextAttribute(h, 15);

			if (turn == 0) {
				board[i][j] = 1;
			} else {
				board[i][j] = -1;
			}

			
			if (isWon()) {
				gotoxy(yAlign, 5);
				cout << " -> GAME WON!" << endl;
				gotoxy(yAlign, 6);
				(turn == 0) ? cout << " -> WINNER: X!" << endl : cout << " -> WINNER: O!" << endl;

				(turn == 0) ? boardState = 1 : boardState = -1;

			}

			turn = (turn == 0);

			mvCount++;

			if (boardState == -2 && mvCount == pow(n, 2)) {
				boardState = 0;
				gotoxy(yAlign, 6);
				cout << " -> GAME DRAW!" << endl;
			}



		} else {
			gotoxy(yAlign, 4);
			cout << " -> INVALID MOVE!" << endl;

		}


	} else if (boardState == -2 && u) {
		

		if (canMove(i, j)) {

			if (turn == 0) {
				board[i][j] = 1;
			} else {
				board[i][j] = -1;
			}


			if (isWon()) {

				(turn == 0) ? boardState = 1 : boardState = -1;


			}

			turn = (turn == 0);

			mvCount++;

			if (boardState == -2 && mvCount == pow(n, 2)) {
				boardState = 0;
			}



		}

	}

}

ticTacToe::~ticTacToe() {

	for (int i = 0; i < n; i++){
		delete[] board[i];
	}
	board = nullptr;

	n = 0;
	boardState = -2;
	turn = 0;
	mvCount = 0;

}
