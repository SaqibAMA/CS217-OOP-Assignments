#include "Monopoly.h"
#include<sstream>
#include<iostream>
using namespace std;

const char* diceTextureImg[6] =
{
	"assets/dice_1.png",
	"assets/dice_2.png",
	"assets/dice_3.png",
	"assets/dice_4.png",
	"assets/dice_5.png",
	"assets/dice_6.png"

};


Monopoly::Monopoly() {

	board.setPlayerCount(0);
	bCoord = new Point[40];
	PropertyAtThisSpace = new Property[20];
	ifstream fin;
	fin.open("files/bCoord.txt");
	Playersarray = new Player[getTotalPlayers()];
	for (int i = 0; !fin.eof(); i++) {

		int x, y;

		fin >> x;
		fin >> y;

		bCoord[i].set(x, y);

		fin.ignore();

	}

	playerPosition = nullptr;


	fin.close();


}

// Getters and Setters

void Monopoly::setTotalPlayers(int totalPlayers) {


	board.setPlayerCount(totalPlayers);
	board.allocatePrevTurns();
	string ab, pur, rent,proid;
	ifstream file("E:\\Monopoly\\monopolyFinalProject\\SFML\\include\\Prices.txt");
	for (int i = 0; !file.eof(); i++)
	{
		getline(file, ab, ' ');
		pur = ab;
		stringstream con1(pur);
		int purchaseis;
		con1 >> purchaseis;
		getline(file, ab, ' ');
		rent = ab;
		stringstream con2(pur);
		int rentis;
		con2 >> rentis;
		PropertyAtThisSpace[i].setpurchaseprice(purchaseis);
		PropertyAtThisSpace[i].setrentprice(rentis);
		PropertyAtThisSpace[i].setMortgaged(false);
		PropertyAtThisSpace[i].setPropertyID(i);
		getline(file, ab, '\n');
	}
	Playersarray = new Player[getTotalPlayers()];
	for (int i = 0; i < getTotalPlayers(); i++)
	{
		Playersarray[i].setPlayerID(i);
		Playersarray[i].setCash(5000);
		
	
	}
}

int Monopoly::getTotalPlayers() {

	return board.getPlayerCount();

}


// Member functions

void Monopoly::printPlayerOnCell(
	sf::RenderWindow& window, sf::RectangleShape shape, int cell,
	int deviation) {

	if ((cell >= 0 && cell <= 10) ||
		(cell >= 21 && cell <= 29)) {

		
		sf::Vector2f playerPos = window.mapPixelToCoords(
			sf::Vector2i(bCoord[cell].x + (deviation * 7), bCoord[cell].y)
		);

		shape.setPosition(playerPos);
	}
	else {

		sf::Vector2f playerPos = window.mapPixelToCoords(
			sf::Vector2i(bCoord[cell].x, bCoord[cell].y + (deviation * 7))
		);

		shape.setPosition(playerPos);

	}

	window.draw(shape);


}

bool Monopoly::canBuildHouse(int group, int playerid)
{
	bool canbuild = true;
	if (group == 0)
	{
		if (Playersarray[playerid].searchInProperty(0) &&
			Playersarray[playerid].searchInProperty(1) &&
			Playersarray[playerid].searchInProperty(2))
		{
			return true;
		}
		else return false;
		
	}
	if (group == 1)
	{
		if (Playersarray[playerid].searchInProperty(3) &&
			Playersarray[playerid].searchInProperty(4) )
		{
			return true;
		}
		else return false;

	}
	if (group == 2)
	{
		if (Playersarray[playerid].searchInProperty(5) &&
			Playersarray[playerid].searchInProperty(6)&&
			Playersarray[playerid].searchInProperty(7))
		{
			return true;
		}
		else return false;

	}
	if (group == 3)
	{
		if (Playersarray[playerid].searchInProperty(8) &&
			Playersarray[playerid].searchInProperty(9) &&
			Playersarray[playerid].searchInProperty(10))
		{
			return true;
		}
		else return false;

	}
	if (group == 4)
	{
		if (Playersarray[playerid].searchInProperty(11) &&
			Playersarray[playerid].searchInProperty(12) &&
			Playersarray[playerid].searchInProperty(13))
		{
			return true;
		}
		else return false;

	}
	if (group == 5)
	{
		if (Playersarray[playerid].searchInProperty(14) &&
			Playersarray[playerid].searchInProperty(15) &&
			Playersarray[playerid].searchInProperty(16))
		{
			return true;
		}
		else return false;

	}
	if (group == 6)
	{
		if (Playersarray[playerid].searchInProperty(17) &&
			Playersarray[playerid].searchInProperty(18) &&
			Playersarray[playerid].searchInProperty(19))
		{
			return true;
		}
		else return false;

	}
}
int Monopoly::convertFromCellToPropertyID(int cell)
{
	if (cell == 1) return 0;
	else if (cell == 3) return 1;
	else if (cell == 6) return 2;
	else if (cell == 8) return 3;
	else if (cell == 9) return 4;
	else if (cell == 11) return 5;
	else if (cell == 13) return 6;
	else if (cell == 14) return 7;
	else if (cell == 16) return 8;
	else if (cell == 18) return 9;
	else if (cell == 19) return 10;
	else if (cell == 21) return 11;
	else if (cell == 23) return 12;
	else if (cell == 24) return 13;
	else if (cell == 26) return 14;
	else if (cell == 27) return 15;
	else if (cell == 29) return 16;
	else if (cell == 31) return 17;
	else if (cell == 32) return 18;
	else if (cell == 34) return 19;
}

void Monopoly::initializePositions() {


	playerPosition = new int[board.getPlayerCount()];

	for (int i = 0; i < board.getPlayerCount(); i++) {
		playerPosition[i] = 0;
	}


}

int Monopoly::getPlayerPosition(int playerID) {

	return playerPosition[playerID];

}

void Monopoly::movePlayer(int playerID, int currRollCount, bool toJail = false) {


	//cout << "\nMoving from " << playerPosition[playerID];

	playerPosition[playerID] += currRollCount;
	playerPosition[playerID] %= 40;
	if (toJail) playerPosition[playerID] = 10;
	if (playerPosition[playerID] == 1 || playerPosition[playerID] == 3 || playerPosition[playerID] == 6 || playerPosition[playerID] == 8
		|| playerPosition[playerID] == 9 || playerPosition[playerID] == 11 || playerPosition[playerID] == 13 || playerPosition[playerID] == 14
		|| playerPosition[playerID] == 16 || playerPosition[playerID] == 18 || playerPosition[playerID] == 19 || playerPosition[playerID] == 21
		|| playerPosition[playerID] == 23 || playerPosition[playerID] == 24 || playerPosition[playerID] == 26 || playerPosition[playerID] == 27
		|| playerPosition[playerID] == 29 || playerPosition[playerID] == 31 || playerPosition[playerID] == 32 || playerPosition[playerID] == 34)
	{
		cout << "It's a private property" << endl;
		int proid = convertFromCellToPropertyID(playerPosition[playerID]);
		if (PropertyAtThisSpace[proid].getOwnerID() == -1)
		{
			cout << "Propertyid = " << PropertyAtThisSpace[proid].getPropertyID()+1 << endl;
			cout<< "This Property is free to be bought.Property Price is "<< PropertyAtThisSpace[proid].getPurchasePrice() << endl;
			cout << "Press 1 to buy.\n2.to Leave."<<endl;
			int choice;
			cin >> choice;
			if (choice == 1)
			{
				PropertyAtThisSpace[proid].setOwnerID(playerID);
				Playersarray[playerID].deductCash(PropertyAtThisSpace[proid].getPurchasePrice());
				Playersarray[playerID].addProperty(PropertyAtThisSpace[proid].getPropertyID());
				cout << Playersarray[playerID].getPlayerID()<<endl;
				cout << "Property bought.\nNew Cash = " << Playersarray[playerID].getCash() << endl;

			}
			else
			{
				int* biding = new int[getTotalPlayers()];
				for (int i = 0; i < getTotalPlayers(); i++)
				{
					biding[i] = 0;

				}
				int bidsize = getTotalPlayers(), bids, maxbid = 0, maxbiddingplayer = -1;
				cout << "This property will now be auctioned." << endl;
				cout << "Submit your bids or press 0 to exit biding." << endl;
				for (int i = 0; bidsize > 0; i++)
				{
					if (i == getTotalPlayers())
					{
						i = 0;
					}
					if (biding[i] != -1)
					{
						cout << "Player " << i + 1 << " Submit your bid: ";
						cin >> bids;


					}
					if (bids == 0)
					{
						biding[i] = -1;
						bidsize--;
					}
					else if (bids > maxbid)
					{
						maxbid = bids;
						cout << "CURRENT MAX BID by Player " << i + 1 << endl;
						maxbiddingplayer = i;
					}
					else if (bids <= maxbid)
					{
						i--;
						cout << "You are not allowed to enter lower than the Current Max bid" << endl;
					}

				}
				if (maxbiddingplayer != -1)
				{
					cout << "Property sold to Player " << maxbiddingplayer << " for " << maxbid << endl;
					Playersarray[maxbiddingplayer].deductCash(maxbid);
					Playersarray[maxbiddingplayer].addProperty(proid);
				}
				else
				{
					cout << "Property stays with bank."<<endl;
				}
			}
		}
		else if (PropertyAtThisSpace[proid].getOwnerID() == playerID)
		{
			int group;
			if (PropertyAtThisSpace[proid].getPropertyID() >= 0 && PropertyAtThisSpace[proid].getPropertyID() <= 2)
			{
				group = 0;
			}
			else if(PropertyAtThisSpace[proid].getPropertyID() >2 && PropertyAtThisSpace[proid].getPropertyID() <= 4)
			{
				group = 1;
			}
			else if (PropertyAtThisSpace[proid].getPropertyID() > 4 && PropertyAtThisSpace[proid].getPropertyID() <= 7)
			{
				group = 2;
			}
			else if (PropertyAtThisSpace[proid].getPropertyID() >7 && PropertyAtThisSpace[proid].getPropertyID() <= 10)
			{
				group = 3;
			}
			else if (PropertyAtThisSpace[proid].getPropertyID() > 10 && PropertyAtThisSpace[proid].getPropertyID() <= 13)
			{
				group = 4;
			}
			else if (PropertyAtThisSpace[proid].getPropertyID() >13  && PropertyAtThisSpace[proid].getPropertyID() <= 16)
			{
				group = 5;
			}
			else if (PropertyAtThisSpace[proid].getPropertyID() >16 && PropertyAtThisSpace[proid].getPropertyID() <= 19)
			{
				group = 6;
			}
			bool canbuild = canBuildHouse(group, playerID);
			
			if (canbuild == true)
			{
				cout << "Property can be upgraded as you own all properties of this group." << endl;
				cout << "Press 1 to upgrade this property to house.\nPress 2 to leave." << endl;
				int enterchoice;
				cin >> enterchoice;
				if (enterchoice == 1)
				{
					Playersarray[playerID].deductCash(100);
					PropertyAtThisSpace[proid].setrentprice(30 / 100 * (PropertyAtThisSpace[proid].getRentPrice()));
					PropertyAtThisSpace[proid].setupgradedlevel(PropertyAtThisSpace[proid].getupgradedlevel()+1);
				}
			}
			else 
			{
				cout << "Property cannot be upgraded as you do not own all properties of this group." << endl;

			}
			
		}
		else
		{
			cout << "It's a private property.It is owned by Player "<< PropertyAtThisSpace[proid].getOwnerID()+1 << endl;
			cout << "Press any key to pay rent of " << PropertyAtThisSpace[proid].getRentPrice()<<endl;
			system("pause");
			Playersarray[playerID].deductCash(PropertyAtThisSpace[proid].getPurchasePrice());
			cout << "Rent Paid.\nNew Cash = " << Playersarray[playerID].getCash() << endl;

		}
	}
	// Set that player to jail as well.

	//cout << "\nTo -> " << playerPosition[playerID] << endl;


}

void Monopoly::playDice(sf::RenderWindow& window,
	sf::RectangleShape* dice, sf::Texture* diceTexture) {


	int* diceNum = board.rollDice();

	if (diceNum[0] > 0 && diceNum[1] > 0 && board.getDRollCount() < 3) {
	

		if (diceNum[0] == diceNum[1] && board.getDRollCount()) {
		
			movePlayer(board.getTurn(), diceNum[0] + diceNum[1]);

		}
		else if (diceNum[0] != diceNum[1] && !board.getDRollCount()) {

			movePlayer(board.getPreviousTurn(), diceNum[0] + diceNum[1]);

		}
		else if (diceNum[0] != diceNum[1] && board.getDRollCount()) {
		
			board.setDRollCount(0);

			movePlayer(board.getPreviousTurn(), diceNum[0] + diceNum[1]);

			board.setTurn(

				(board.getTurn() + 1) % board.getPlayerCount()

			);

		}
	}
	else {

		if (board.getDRollCount() == 3) {

			movePlayer(board.getPreviousTurn(), 0, true);

			
			board.setPreviousTurn(

				board.getTurn()

			);

			board.setDRollCount(0);

		}

	}

	
}

void Monopoly::updateDiceTextures(sf::Texture* diceTexture) {


	diceTexture[0].loadFromFile(
		diceTextureImg[
			board.getPrevTurns()[board.getPlayerCount() - 1][0]
				- (board.getPrevTurns()[board.getPlayerCount() - 1][0] > 0)
		]
	);

	diceTexture[1].loadFromFile(
		diceTextureImg[
			board.getPrevTurns()[board.getPlayerCount() - 1][1]
				- (board.getPrevTurns()[board.getPlayerCount() - 1][1] > 0)
		]
	);


}


// Destructor

Monopoly::~Monopoly() {

}