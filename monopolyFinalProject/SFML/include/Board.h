#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <Space.h>
#include "PrivateProperty.h"
#include "CommercialProperty.h"
#include "Player.h"
#include "Card.h"
#include <fstream>

using namespace std;


#pragma once
class Board
{

private:
	int** prevTurns;
	int previousTurn;
	int playerCount;
	int turn;				// keeps the turn of the player
	int dRollCount;			// keeps track of double rolls
	int currRollAmount;		// keep the amount of steps that
							// a user has accumulated

	Player** players;

	Space** cells;
	int jailPosition;

	Card** Chance;				// Added 04th June
	Card** CommunityChest;

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

	int getCurrRollAmount();
	void setCurrRollAmount(int);

	int getJailPosition();

	Player** getPlayers();
	
	void allocatePlayers();

	Space** getCells();


	void executeCard(Card&);
	void shufflecards();


	/// New
	void isAtGo(Player& a);
	void goToJail(Player& a);

	~Board();
};