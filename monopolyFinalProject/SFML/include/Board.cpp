#include "Board.h"


Board::Board() {

	prevTurns = nullptr;
	playerCount = 0;

	turn = 0;
	dRollCount = 0;

	srand(time(0));

	previousTurn = 0;

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


	cout << "turn -> " << turn << endl;

	int* diceNum = new int[2];

	diceNum[0] = rand() % 6 + 1;
	diceNum[1] = rand() % 6 + 1;

	for (int i = 0; i < 2; i++) {
	
		prevTurns[i][0] = prevTurns[i + 1][0];
		prevTurns[i][1] = prevTurns[i + 1][1];

	}

	prevTurns[2][0] = diceNum[0];
	prevTurns[2][1] = diceNum[1];

	if (diceNum[0] != diceNum[1]) {
	
		turn++;
		turn = turn % playerCount;

		dRollCount = 0;

	}
	else {
		
		dRollCount++;

		if (dRollCount == 3) {

			diceNum[0] = -1;
			diceNum[0] = -1;

			cout << "dCount hit 3!" << endl;

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

Board::~Board() {





}