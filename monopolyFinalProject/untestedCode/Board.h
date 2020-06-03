#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Space.h"
#include "PrivateProperty.h"
#include "Card.h"
#include "Player.h"

using namespace std;


#pragma once
//UPDATE 5/29/2020
//NEW DATA MEMBERS ADDED
class Board
{

private:
	//NEW DATA MEMBERS ADDED
	int** prevTurns;
	int previousTurn;
	int playerCount;
	int turn;				// keeps the turn of the player
	int dRollCount;			// keeps track of double rolls
	int currRollAmount;		// keep the amount of steps that
	
	Player** players;					// a user has accumulated
	Space** cells;
	Card** Chance;
	Card** CommunityChest;

public:
	//NEW FUNCTIONS ADDED
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

	int getCurrRollAmount();
	void setCurrRollAmount(int);

	void executeCard(Card&);
	void shufflecards();
	~Board();
};