#include "uTicTacToe.h"
#include "ticTacToe.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <fstream>

using namespace std;

extern void gotoxy(int x, int y);
extern HANDLE h;

uTicTacToe::uTicTacToe() {

	n = 3;

	boardArray = new int***[n];

	for (int i = 0; i < n; i++)
		boardArray[i] = new int**[n];


	boardStates = new int*[n];

	for (int i = 0; i < n; i++)
		boardStates[i] = new int[3];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
		
			boardArray[i][j] = game[i][j].getBoard();
			boardStates[i][j] = game[i][j].getBoardState();

		}
	}

	turn = 0;
	mvCount = 0;

	enI = -1;
	enJ = -1;

	gameWon = false;


}

void uTicTacToe::printBoardAtLocation(int** boardArray, int yAlign, int xAlign) {

	char buff;


	gotoxy(yAlign, xAlign);
	cout << "                              ";
	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {

			gotoxy(yAlign + (j*10), xAlign + (2*i) + 1);

			if (boardArray[i][j] == 0) {
				buff = '-';
			}
			else if (boardArray[i][j] == -1) {
				buff = 'O';
			}
			else {
				buff = 'X';
			}

			cout << setw(5) << buff << setw(5) << " ";

			gotoxy(yAlign + (j*10), xAlign + (2*i) + 2);
			cout << setw(5) << " " << setw(5) << " ";

		}

	}

}

void uTicTacToe::print() {

	int yAlign = 10;
	int xAlign = 4;

	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
		
			printBoardAtLocation(boardArray[i][j], yAlign, xAlign);

			yAlign += 32;

		}
		
		yAlign = 10;
		xAlign += 8;

	}

	cout << endl;

	SetConsoleTextAttribute(h, 0);

	gotoxy(yAlign, 1);
	cout << "-> ULTIMATE TIC TAC TOE!" << endl;
	gotoxy(yAlign, 2);
	cout << "-> ACTIVE BOARD: ";
	gotoxy(yAlign + 18, 2);
	cout << "      " << endl;
	gotoxy(yAlign + 30, 2);
	(turn == 0) ? cout << "-> CURRENT TURN: X!" :
		cout << "-> CURRENT TURN: O!";

	SetConsoleTextAttribute(h, 15);

	gotoxy(yAlign, 1);
	cout << "-> ULTIMATE TIC TAC TOE!" << endl;
	gotoxy(yAlign, 2);
	cout << "-> ACTIVE BOARD: ";
	gotoxy(yAlign + 18, 2);
	(enI == -1 || enJ == -1) ? cout << "ANY" << endl :
		cout << "" << (3*enI) + enJ << endl;
	gotoxy(yAlign + 30, 2);
	(turn == 0) ? cout << "-> CURRENT TURN: X!" :
		cout << "-> CURRENT TURN: O!";

}

void uTicTacToe::setGlobalTurn() {
	
	(turn == 0) ? turn = 1 : turn = 0;

	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
			
			game[i][j].setTurn(turn);

		}

	}

}

void uTicTacToe::updateBoardStates() {
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
		
			boardStates[i][j] = game[i][j].getBoardState();

		}
	}

}

bool uTicTacToe::canMove(int eI, int eJ, int i, int j) {
	
	if (boardArray[eI][eJ][i][j] != 0 || i >= n || i < 0 || j >= n || j < 0) return false;

	return true;

}

void uTicTacToe::makeMove(int i, int j, bool u) {

	if (enI == -1 || enJ == -1) {
		
		enI = getBoardRow();
		enJ = getBoardCol();

	}


	if (canMove(enI, enJ, i, j)) {

		if (!gameWon) {
			game[enI][enJ].makeMove(i, j, true);

			if (boardStates[i][j] != -2) {
				enI = -1;
				enJ = -1;
			} else {
				enI = i;
				enJ = j;
			}

			mvCount++;

		}

		updateBoardStates();


		if (isWon()) {

			(h, 15);
			gotoxy(70, 2);
			(turn == 0) ? cout << "-> GAME WON by X!" << endl
				: cout << "-> GAME WON by O!" << endl;
			gameWon = true;

		}

		setGlobalTurn();


	}

}

int uTicTacToe::getBoardRow() {
	
	int row = 0;
	int yAlign = 5;

	(h, 15);
	gotoxy(yAlign, 7);
	cout << "-> " << endl;

	// 8 is the difference

	while (true) {
	
		if (row > 0 && (GetAsyncKeyState(VK_UP) & 0x26000)) {

			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign, row*8 + 7);
			cout << "-> " << endl;

			SetConsoleTextAttribute(h, 15);

			row--;
			gotoxy(yAlign, row*8 + 7);
			cout << "-> " << endl;

		} else if (row < n - 1 && (GetAsyncKeyState(VK_DOWN) & 0x28000)) {

			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign, row*8 + 7);
			cout << "-> " << endl;
			

			SetConsoleTextAttribute(h, 15);

			row++;
			gotoxy(yAlign, row*8 + 7);
			cout << "-> " << endl;

		} else if (GetAsyncKeyState(VK_SPACE) & 0x20000) {
			
			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign, row*8 + 7);
			cout << "-> " << endl;

			SetConsoleTextAttribute(h, 15);

			return row;

		}

	}

	return 0;

}

int uTicTacToe::getBoardCol() {
	
	int col = 0;
	int yAlign = 23;
	int xAlign = 28;

	(h, 15);
	gotoxy(yAlign, xAlign);
	cout << " ^ " << endl;

	// 32 is the difference

	while (true) {
	
		if (col > 0 && (GetAsyncKeyState(VK_LEFT) & 0x25000)) {

			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + col * 32, xAlign);
			cout << " ^ " << endl;

			SetConsoleTextAttribute(h, 15);

			col--;
			gotoxy(yAlign + col * 32, xAlign);
			cout << " ^ " << endl;

		} else if (col < n - 1 && (GetAsyncKeyState(VK_RIGHT) & 0x27000)) {

			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + col * 32, xAlign);
			cout << " ^ " << endl;
			

			SetConsoleTextAttribute(h, 15);

			col++;
			gotoxy(yAlign + col * 32, xAlign);
			cout << " ^ " << endl;

		} else if (GetAsyncKeyState(VK_SPACE) & 0x20000) {

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + col * 32, xAlign);
			cout << " ^ " << endl;

			SetConsoleTextAttribute(h, 15);

			Sleep(200);
			return col;

		}

	}

	return 0;

}

int uTicTacToe::getRow() {
	
	int yAlign = 5;
	int row = 0;

	int devX, devY;

	(enI == -1) ? devX = 0 : devX = enI * 8;
	(enJ == -1) ? devY = 0 : devY = (enJ * 32) + 3;

	gotoxy(yAlign + devY, 5 + devX);
	cout << ">" << endl;

	
	while (true) {
		
		if (row > 0 && (GetAsyncKeyState(VK_UP) & 0x26000)) {

			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + devY, row*2 + 5 + devX);
			cout << ">" << endl;

			SetConsoleTextAttribute(h, 15);

			row--;
			gotoxy(yAlign + devY, row*2 + 5 + devX);
			cout << ">" << endl;

		} else if (row < n - 1 && (GetAsyncKeyState(VK_DOWN) & 0x28000)) {

			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + devY, row*2 + 5 + devX);
			cout << ">" << endl;
			

			SetConsoleTextAttribute(h, 15);

			row++;
			gotoxy(yAlign + devY, row*2 + 5 + devX);
			cout << ">" << endl;

		} else if (GetAsyncKeyState(VK_SPACE) & 0x20000) {
			
			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + devY, row*2 + 5 + devX);
			cout << ">" << endl;

			SetConsoleTextAttribute(h, 15);

			return row;

		} else if (GetAsyncKeyState(0x53) & 0x53000) {
			
			Sleep(200);
			saveGame();

		} else if (GetAsyncKeyState(0x4C) & 0x4C000) {
			
			Sleep(200);
			loadGame();
			print();

		}

	}

	return 0;

}

int uTicTacToe::getCol() {
	
	int col = 0;
	
	int yAlign = 13;

	int devX, devY;

	(enI == -1) ? devX = 0 : devX = enI * 8;
	(enJ == -1) ? devY = 0 : devY = (enJ * 32);

	SetConsoleTextAttribute(h, 15);

	gotoxy(yAlign + col + devY, 5 + (2 * n) + devX);
	cout << " ^ " << endl;

	
	while (true) {
		
		if (col > 0 && (GetAsyncKeyState(VK_LEFT) & 0x25000)) {

			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + col * 10 + devY, 5 + (2 * n) + devX);
			cout << " ^ " << endl;

			SetConsoleTextAttribute(h, 15);

			col--;
			gotoxy(yAlign + col * 10 + devY, 5 + (2 * n) + devX);
			cout << " ^ " << endl;

		} else if (col < n - 1 && (GetAsyncKeyState(VK_RIGHT) & 0x27000)) {

			Sleep(200);

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + col * 10 + devY, 5 + (2 * n) + devX);
			cout << " ^ " << endl;
			

			SetConsoleTextAttribute(h, 15);

			col++;
			gotoxy(yAlign + col * 10 + devY, 5 + (2 * n) + devX);
			cout << " ^ " << endl;

		} else if (GetAsyncKeyState(VK_SPACE) & 0x20000) {

			SetConsoleTextAttribute(h, 0);
			gotoxy(yAlign + col * 10 + devY, 5 + (2 * n) + devX);
			cout << " ^ " << endl;
			SetConsoleTextAttribute(h, 15);

			Sleep(200);
			return col;

		}
	}


}

void uTicTacToe::saveGame() {
	
	ofstream fout;
	fout.open("uGame.txt");


	// Boards
	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
		
			for (int k = 0; k < n; k++) {
				
				for (int l = 0; l < n; l++) {
				
					fout << boardArray[i][j][k][l] << " ";

				}

				fout << endl;

			}

		}

	}

	// Board States
	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
			
			fout << boardStates[i][j] << " ";

		}

		fout << endl;

	}

	// mvCount
	fout << mvCount << endl;

	// enI, enJ
	fout << enI << endl;
	fout << enJ << endl;


	fout.close();


}

bool uTicTacToe::isDraw() {
	
	return (mvCount == 81);

}

bool uTicTacToe::isWon() {

	bool gameWonH = true;
	bool gameWonV = true;
	bool gameWonD = true;

	for (int i = 0; i < n; i++) {

		// Checking horizontal
		gameWonH = true;

		for (int j = 0; j < n - 1 && gameWonH; j++) {

			(boardStates[i][j] == 0 || boardStates[i][j] == -2) ? gameWonH = false : gameWonH = !(boardStates[i][j] != boardStates[i][j + 1]);

		}

		if (gameWonH) return gameWonH;


		// Checking vertical
		gameWonV = true;

		for (int j = 0; j < n - 1 && gameWonV; j++) {
			
			(boardStates[j][i] == 0 || boardStates[j][i] == -2) ? gameWonV = false : gameWonV = !(boardStates[j][i] != boardStates[j + 1][i]);

		}

		if (gameWonV) return gameWonV;

	}

	// Checking diagonal (right to left)
	gameWonD = true;

	for (int j = 0; j < n - 1 && gameWonD; j++) {
			
		(boardStates[j][j] == 0 || boardStates[j][j] == -2) ? gameWonD = false : gameWonD = !(boardStates[j][j] != boardStates[j + 1][j + 1]);

	}

	if (gameWonD) return gameWonD;


	// Checking diagonal (left to right)
	gameWonD = true;

	for (int i = n - 1, j = 0; i > 0 && gameWonD; i--, j++) {

		(boardStates[j][i] == 0 || boardStates[j][i] == -2) ? gameWonD = false : gameWonD = !(boardStates[j][i] != boardStates[j + 1][i - 1]);

	}

	if (gameWonD) return gameWonD;


	return false;

}

void uTicTacToe::loadGame() {
	
	ifstream fin;
	fin.open("uGame.txt");

	// Loading boards
	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
		
			for (int k = 0; k < n; k++) {
				
				for (int l = 0; l < n; l++) {
				
					fin >> boardArray[i][j][k][l];

				}

				fin.ignore();

			}

		}

	}

	// Board States
	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
			
			fin >> boardStates[i][j];

		}

		fin.ignore();

	}

	// mvCount
	fin >> mvCount;
	fin.ignore();

	// enI, enJ
	fin >> enI;
	fin.ignore();

	fin >> enJ;
	fin.ignore();

	fin.close();

}

uTicTacToe::~uTicTacToe() {

	for (int i = 0; i < n; i++) {
		
		for (int j = 0; j < n; j++) {
			
			for (int k = 0; k < n; k++) {
				
				delete[] boardArray[i][j][k];

			}

			delete[] boardArray[i][j];

		}

		delete[] boardArray[i];

	}

	delete[] boardArray;

	boardArray = nullptr;

	for (int i = 0; i < n; i++)
		delete[] boardStates[i];

	delete[] boardStates;
	boardStates = nullptr;

}
