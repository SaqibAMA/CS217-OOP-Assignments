#include "Board.h"


Board::Board() {

	players = nullptr;

	prevTurns = nullptr;
	playerCount = 0;

	turn = 0;
	dRollCount = 0;

	srand(time(0));

	previousTurn = 0;

	currRollAmount = 0;

	jailPosition = 10;



	// Initializing Board Cells

	cells = new Space * [40];


	// Special Spaces

	int specialSpaces[12] = {
		0, 2, 4, 7,
		10, 17, 20, 22,
		30, 33, 36, 38
	};

	for (int i = 0; i < 12; i++)
		cells[specialSpaces[i]] = new Space;

	int privatePropertySpaces[20] = {
	
		1, 3, 6, 8,
		9, 11, 13, 14,
		16, 18, 19, 21,
		23, 24, 26, 27,
		29, 31, 32, 34,

	};

	for (int i = 0; i < 20; i++)
		cells[privatePropertySpaces[i]] = new PrivateProperty;

	
	int commercialPropertySpaces[8] = {
	
		5, 12, 15, 25,
		28, 35, 37, 39
	
	};

	for (int i = 0; i < 8; i++)
		cells[commercialPropertySpaces[i]] = new CommercialProperty;

}

int Board::getPlayerCount() {

	return playerCount;

}

void Board::setPlayerCount(int playerCount) {

	this->playerCount = playerCount;

}

void Board::allocatePrevTurns() {

	prevTurns = new int*[playerCount];

	for (int i = 0; i < playerCount; i++) {
		prevTurns[i] = new int[2];

		for (int j = 0; j < 2; j++)
			prevTurns[i][j] = 0;

	}

}

int** Board::getPrevTurns() {
	return prevTurns;
}

int* Board::rollDice() {

	int* diceNum = new int[2];

	diceNum[0] = rand() % 6 + 1;
	diceNum[1] = rand() % 6 + 1;


	for (int i = 0; i < playerCount - 1; i++) {
	
		prevTurns[i][0] = prevTurns[i + 1][0];
		prevTurns[i][1] = prevTurns[i + 1][1];

	}

	prevTurns[playerCount - 1][0] = diceNum[0];
	prevTurns[playerCount - 1][1] = diceNum[1];


	if (diceNum[0] != diceNum[1]) {

		previousTurn = turn;

		if (dRollCount) {
			dRollCount = 0;
		}

		turn = (turn + 1) % playerCount;

	}
	else {

		dRollCount++;

		if (dRollCount == 3) {

			diceNum[0] = -1;
			diceNum[1] = -1;

			//cout << "dCount hit 3!" << endl;

			/*turn++;
			turn = turn % playerCount;*/

			currRollAmount = 0;

		}

	}


	return diceNum;


}


int Board::getDRollCount() { return dRollCount; }

void Board::setDRollCount(int dRollCount) {
	this->dRollCount = dRollCount;
}


int Board::getTurn() {

	return turn;

}

void Board::setTurn(int turn) {

	this->turn = turn;

}

int Board::getPreviousTurn() {
	return previousTurn; 
}

void Board::setPreviousTurn(int previousTurn) {
	this->previousTurn = previousTurn; 
}

int Board::getCurrRollAmount() { return currRollAmount; }

void Board::setCurrRollAmount(int currRollAmount) {
	this->currRollAmount = currRollAmount;
}

int Board::getJailPosition() {
	return jailPosition;
}

Player** Board::getPlayers() {

	return players;

}

void Board::allocatePlayers() {

	this->players = new Player * [playerCount];

	for (int i = 0; i < playerCount; i++)
		this->players[i] = new Player("Saqib", i);

}

Space** Board::getCells() {
	return cells;
}

Board::~Board() {





}