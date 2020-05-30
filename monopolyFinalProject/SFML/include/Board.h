#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;


#pragma once
class Board
{

private:
	int** prevTurns;
	int previousTurn;
	int playerCount;
	int turn;		// keeps the turn of the player
	int dRollCount;	// keeps track of double rolls

public:
	Board();

	int getPlayerCount();
	void setPlayerCount(int);

	void allocatePrevTurns();
	int** getPrevTurns();

	int* rollDice();

	int getDRollCount();
	void setDRollCount(int);

	int getTurn();
	void setTurn(int);

	int getPreviousTurn();
	void setPreviousTurn(int);


	~Board();
};