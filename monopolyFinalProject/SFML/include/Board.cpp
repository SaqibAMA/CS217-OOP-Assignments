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



	// 6th June

	// Review

	ifstream chanceCardsFile;
	ifstream communityChestFile;
	chanceCardsFile.open("Chance.txt");
	communityChestFile.open("CommunityChest.txt");

	Chance = new Card * [15];
	CommunityChest = new Card * [15];
	for (int i = 0; i < 15; i++) {
		Chance[i] = new ChanceCard;
		CommunityChest[i] = new CommunityCard;
	}
	for (int i = 0; i < 15; i++) {
		char CCtemp[200];
		char CCCtemp[200];
		chanceCardsFile.getline(CCtemp, 200);
		communityChestFile.getline(CCCtemp, 200);
		Chance[i]->setCardAction(CCtemp);
		CommunityChest[i]->setCardAction(CCCtemp);
		Chance[i]->setCardID(i);
		CommunityChest[i]->setCardID(i);
	}

	chanceCardsFile.close();
	communityChestFile.close();

	shufflecards();



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




// 6th June


// Review

void Board::executeCard(Card& C) {
	int type = 0;
	type = C.getCardType();
	if (type == 0) {
		int id = C.getCardID();
		if (id == 0) {
			players[turn]->setPlayerPosition(0);
			players[turn]->setCash(players[turn][0].getCash() + 300);
			cells[0]->putsPlayersOnSpace(turn);
		}
		if (id == 1) {
			if (players[turn]->getPlayerPosition() > 26) {
				players[turn]->setCash(500);
			}
			players[turn]->setPlayerPosition(26);
			cells[26]->putsPlayersOnSpace(turn);
		}
		if (id == 2) {
			int pos = 0;
			bool check = false;
			int index = 0;
			pos = players[turn]->getPlayerPosition();
			if (pos >= 0 && pos < 12) {
				players[turn]->setPlayerPosition(12);
				cells[12]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 12) {
							check = true;
							index = i;
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (5 * currRollAmount));
					players[turn]->setCash(players[turn]->getCash() - (5 * currRollAmount));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
			if (pos > 12 && pos < 28) {
				players[turn]->setPlayerPosition(28);
				cells[28]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 28) {
							check = true;
							index = i;
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (5 * currRollAmount));
					players[turn]->setCash(players[turn]->getCash() - (5 * currRollAmount));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
			if (pos > 28 && pos < 37) {
				players[turn]->setPlayerPosition(37);
				cells[37]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 37) {
							check = true;
							index = i;
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (5 * currRollAmount));
					players[turn]->setCash(players[turn]->getCash() - (5 * currRollAmount));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
		}
		if (id == 3) {
			int pos = 0;
			int index = 0;
			bool check = false;
			int rent = 0;
			pos = players[turn]->getPlayerPosition();
			if (pos >= 0 && pos < 5) {
				players[turn]->setPlayerPosition(5);
				cells[5]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 5) {
							check = true;
							index = i;
							rent = temp[i]->getRentPrice();
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (2 * rent));
					players[turn]->setCash(players[turn]->getCash() - (2 * rent));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
			if (pos > 5 && pos < 15) {
				players[turn]->setPlayerPosition(15);
				cells[15]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 15) {
							check = true;
							index = i;
							rent = temp[i]->getRentPrice();
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (2 * rent));
					players[turn]->setCash(players[turn]->getCash() - (2 * rent));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
			if (pos > 15 && pos < 25) {
				players[turn]->setPlayerPosition(25);
				cells[25]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 25) {
							check = true;
							index = i;
							rent = temp[i]->getRentPrice();
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (2 * rent));
					players[turn]->setCash(players[turn]->getCash() - (2 * rent));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
			if (pos > 25 && pos < 35) {
				players[turn]->setPlayerPosition(35);
				cells[35]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 35) {
							check = true;
							index = i;
							rent = temp[i]->getRentPrice();
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (2 * rent));
					players[turn]->setCash(players[turn]->getCash() - (2 * rent));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
		}
		if (id == 4) {
			int pos = 0;
			int index = 0;
			bool check = false;
			int rent = 0;
			pos = players[turn]->getPlayerPosition();
			if (pos >= 0 && pos < 5) {
				players[turn]->setPlayerPosition(5);
				cells[5]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 5) {
							check = true;
							index = i;
							rent = temp[i]->getRentPrice();
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (2 * rent));
					players[turn]->setCash(players[turn]->getCash() - (2 * rent));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
			if (pos > 5 && pos < 15) {
				players[turn]->setPlayerPosition(15);
				cells[15]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 15) {
							check = true;
							index = i;
							rent = temp[i]->getRentPrice();
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (2 * rent));
					players[turn]->setCash(players[turn]->getCash() - (2 * rent));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
			if (pos > 15 && pos < 25) {
				players[turn]->setPlayerPosition(25);
				cells[25]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 25) {
							check = true;
							index = i;
							rent = temp[i]->getRentPrice();
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (2 * rent));
					players[turn]->setCash(players[turn]->getCash() - (2 * rent));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
			if (pos > 25 && pos < 35) {
				players[turn]->setPlayerPosition(35);
				cells[35]->putsPlayersOnSpace(turn);
				for (int i = 0; i < playerCount && check == false; i++) {
					PrivateProperty** temp = (PrivateProperty**)players[i]->getPropertyList();
					for (int i = 0; i < players[i]->getPropertyListSize() && check == false; i++) {
						if (temp[i]->getPropertyID() == 35) {
							check = true;
							index = i;
							rent = temp[i]->getRentPrice();
						}
					}
				}
				if (check == true) {
					players[index]->setCash(players[index]->getCash() + (2 * rent));
					players[turn]->setCash(players[turn]->getCash() - (2 * rent));
				}
				else {
					//BUY PROPERTY FUNTION HAS TO BE CALLED HERE
				}
			}
		}
		if (id == 5) {
			int pos = players[turn]->getPlayerPosition();
			if (pos >= 0 && pos < 15) {
				players[turn]->setPlayerPosition(16);
				cells[16]->putsPlayersOnSpace(turn);
			}
			else {
				players[turn]->setPlayerPosition(16);
				cells[16]->putsPlayersOnSpace(turn);
				players[turn]->setCash(players[turn][0].getCash() + 300);
			}

		}
		if (id == 6) {
			players[turn]->setCash(players[turn][0].getCash() + 100);
		}
		if (id == 7) {
			players[turn]->setHasJailRescueCard(players[turn]->getHasJailRescueCard() + 1);
		}
		if (id == 8) {
			if (players[turn]->getPlayerPosition() >= 4) {
				players[turn]->setPlayerPosition(players[turn]->getPlayerPosition() - 4);
				cells[players[turn]->getPlayerPosition() - 4]->putsPlayersOnSpace(turn);
			}
			else {
				players[turn]->setPlayerPosition(38);
				cells[38]->putsPlayersOnSpace(turn);
			}
		}
		if (id == 9) {
			int price = 0;
			PrivateProperty** temp = (PrivateProperty**)players[turn]->getPropertyList();
			for (int i = 0; i < players[turn]->getPropertyListSize(); i++) {
				price = price + temp[i]->getHouseCount() * 50;
				price = price + temp[i]->getHotelCount() * 100;
			}
			players[turn]->setCash(players[turn][0].getCash() - price);
		}
		if (id == 10) {
			players[turn]->setCash(players[turn][0].getCash() - 25);
		}
		if (id == 11) {
			players[turn]->setCash(players[turn][0].getCash() - ((playerCount - 1) * 25));
			for (int i = 0; i < playerCount; i++) {
				if (i != turn) {
					players[i]->setCash(players[i]->getCash() + 25);
				}
			}
		}
		if (id == 12) {
			players[turn]->setCash(players[turn]->getCash() + 150);
		}
		if (id == 13) {
			if (players[turn]->getPlayerPosition() > 35) {
				players[turn]->setCash(players[turn]->getCash() + 500);
			}
			players[turn]->setPlayerPosition(35);
			cells[35]->putsPlayersOnSpace(turn);
		}
		if (id == 14) {
			if (players[turn]->getPlayerPosition() > 4) {
				players[turn]->setCash(players[turn]->getCash() + 500);
			}
			players[turn]->setPlayerPosition(4);
			cells[4]->putsPlayersOnSpace(turn);
		}
	}
	else {
		int id = C.getCardID();
		if (id == 0) {
			players[turn]->setPlayerPosition(0);
			cells[0]->putsPlayersOnSpace(turn);
			players[turn]->setCash(players[turn][0].getCash() + 400);
		}
		if (id == 1) {
			players[turn]->setCash(players[turn][0].getCash() + 200);
		}
		if (id == 2) {
			players[turn]->setCash(players[turn][0].getCash() - 200);
		}
		if (id == 3) {
			players[turn]->setCash(players[turn][0].getCash() + 50);
		}
		if (id == 4) {
			players[turn]->setHasJailRescueCard(players[turn]->getHasJailRescueCard() + 1);
		}
		if (id == 5) {
			players[turn]->setCash(players[turn][0].getCash() + 150);
		}
		if (id == 6) {
			players[turn]->setCash(players[turn][0].getCash() + 200);
		}
		if (id == 7) {
			players[turn]->setCash(players[turn][0].getCash() - 100);
		}
		if (id == 8) {
			players[turn]->setCash(players[turn][0].getCash() - 200);
		}
		if (id == 9) {
			players[turn]->setCash(players[turn][0].getCash() + 50);
		}
		if (id == 10) {
			int price = 0;
			PrivateProperty** temp = (PrivateProperty**)players[turn]->getPropertyList();
			for (int i = 0; i < players[turn]->getPropertyListSize(); i++) {
				price = price + temp[i]->getHouseCount() * 50;
				price = price + temp[i]->getHotelCount() * 125;
			}
			players[turn]->setCash(players[turn][0].getCash() - price);
		}
		if (id == 11) {
			players[turn]->setCash(players[turn][0].getCash() + 300);
		}
		if (id == 12) {
			players[turn]->setCash(players[turn][0].getCash() - 50);
		}
		if (id == 13) {
			players[turn]->setCash(players[turn][0].getCash() - 80);
		}
		if (id == 14) {
			players[turn]->setCash(players[turn][0].getCash() - 50);
		}
	}
}

void Board::shufflecards() {
	int num1 = 0;
	srand((unsigned)time(0));
	num1 = (rand() % 6) + 1;
	for (int i = 0; i < num1; i++) {
		for (int i = 0; i < 14; i++) {
			swap(Chance[i], Chance[i + 1]);
			swap(CommunityChest[i], CommunityChest[i + 1]);
		}
	}
	for (int i = 0; i < 15; i++) {
		cout << CommunityChest[i]->getCardAction() << " " << CommunityChest[i]->getCardID() << endl;
	}
	cout << endl;
	for (int i = 0; i < 15; i++) {
		cout << Chance[i]->getCardAction() << " " << Chance[i]->getCardID() << endl;
	}
}


// REVIEW

// NEW FUNNCTIONS
void Board::isAtGo(Player& a) {
	if (a.getPlayerPosition() == 20) {
		a.addCash(500);
	}
}
void Board::goToJail(Player& a) {
	if (a.getPlayerPosition() == 30) {
		// GO TO JAIL per ha
		a.setPlayerPosition(10);
	}

}



Board::~Board() {





}