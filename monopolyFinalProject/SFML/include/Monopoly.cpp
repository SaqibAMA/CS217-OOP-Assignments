#include "Monopoly.h"

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

	ifstream fin;
	fin.open("files/bCoord.txt");

	for (int i = 0; !fin.eof(); i++) {

		int x, y;

		fin >> x;
		fin >> y;

		bCoord[i].set(x, y);

		fin.ignore();

	}

	playerPosition = nullptr;

	dealChoice = -1;


	fin.close();


}

// Getters and Setters

void Monopoly::setTotalPlayers(int totalPlayers) {


	board.setPlayerCount(totalPlayers);
	board.allocatePrevTurns();
	board.allocatePlayers();

}

int Monopoly::getTotalPlayers() {

	return board.getPlayerCount();

}

Board Monopoly::getBoard() {
	return board;
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


void Monopoly::initializePositions() {


	playerPosition = new int[board.getPlayerCount()];

	for (int i = 0; i < board.getPlayerCount(); i++) {
		playerPosition[i] = 0;
	}


}

int Monopoly::getPlayerPosition(int playerID) {

	return playerPosition[playerID];

}

void Monopoly::movePlayer(int playerID, int currRollCount, sf::RenderWindow& window, bool toJail = false) {


	//cout << "\nMoving from " << playerPosition[playerID];

	playerPosition[playerID] += currRollCount;
	playerPosition[playerID] %= 40;
	board.getPlayerByID(playerID)->setPlayerPosition(playerPosition[playerID]);
	if (toJail || playerPosition[playerID] == 30) playerPosition[playerID] = 10;

	board.putPlayerOnSpace(playerPosition[playerID], playerID, window, dealChoice);


	// Set that player to jail as well.

	//cout << "\nTo -> " << playerPosition[playerID] << endl;


}

void Monopoly::playDice(sf::RenderWindow& window,
	sf::RectangleShape* dice, sf::Texture* diceTexture, bool existsInProp) {

	int* diceNum = board.rollDice();

	//if (existsInProp) {

	board.getPlayerByID(board.getTurn())->setIsRenting(-1);

	if (diceNum[0] > 0 && diceNum[1] > 0 && board.getDRollCount() < 3) {


		if (diceNum[0] == diceNum[1] && board.getDRollCount()) {

			movePlayer(board.getTurn(), diceNum[0] + diceNum[1], window);

		}
		else if (diceNum[0] != diceNum[1] && !board.getDRollCount()) {

			movePlayer(board.getPreviousTurn(), diceNum[0] + diceNum[1], window);

		}
		else if (diceNum[0] != diceNum[1] && board.getDRollCount()) {

			board.setDRollCount(0);

			movePlayer(board.getPreviousTurn(), diceNum[0] + diceNum[1], window);

			board.setTurn(

				(board.getTurn() + 1) % board.getPlayerCount()

			);

		}
	}
	else {

		if (board.getDRollCount() == 3) {

			movePlayer(board.getTurn(), 0, window, true);


			board.setTurn(

				(board.getTurn() + 1)
				% board.getPlayerCount()

			);

			board.setDRollCount(0);

		}

	}
	//}

	
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


Bank Monopoly::getBank() {
	return bank;
}


void Monopoly::setDealChoice(int dealChoice) {

	this->dealChoice = dealChoice;

}


// REVIEW

/***
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
			Playersarray[playerid].searchInProperty(4))
		{
			return true;
		}
		else return false;

	}
	if (group == 2)
	{
		if (Playersarray[playerid].searchInProperty(5) &&
			Playersarray[playerid].searchInProperty(6) &&
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
**/





// Destructor

Monopoly::~Monopoly() {


}



void Monopoly::loadGame() {
	ifstream SavedGame;
	SavedGame.open("Saved.txt");
	int count = 0;
	int i = 0;
	SavedGame >> count;
	setTotalPlayers(count);
	while (!SavedGame.eof()) {
		Property** propertylist;
		int id = i;
		char* temp = new char[20];
		int cash;
		int propertySize = 0;
		bool isInJail;
		int hasJailRescueCard;
		bool isbankrupt;
		int playerPosition;
		int inJailCount;
		bool hasWifi;
		bool hasGas;
		bool hasElectricity;
		SavedGame >> temp;
		SavedGame >> cash;
		SavedGame >> propertySize;
		Property** plots = new  Property * [propertySize];
		for (int i = 0; i < propertySize; i++) {
			plots[i] = new Property;
		}
		int ProID;
		int check = 0;
		for (int i = 0; i < propertySize; i++) {
			SavedGame >> ProID;
			plots[i] = bank.getProperty(ProID);
			bank.appendPropertyList(bank.getProperty(ProID));
			SavedGame >> check;
			for (int i = 0; i < check; i++) {
				plots[i]->addHouse();
			}
			SavedGame >> check;
			for (int i = 0; i < check; i++) {
				plots[i]->addShop();
			}
			SavedGame >> check;
			for (int i = 0; i < check; i++) {
				plots[i]->addHotel();
			}
			SavedGame >> hasWifi;
			if (hasWifi == true) {
				plots[i]->addWifi();
			}
			SavedGame >> hasGas;
			if (hasGas == true) {
				plots[i]->addGas();
			}
			SavedGame >> hasElectricity;
			if (hasElectricity == true) {
				plots[i]->addElectricity();
			}
		}
		SavedGame >> isInJail;
		SavedGame >> hasJailRescueCard;
		SavedGame >> isbankrupt;
		SavedGame >> playerPosition;
		SavedGame >> inJailCount;
		board.setPlayerData(id, temp, cash, propertySize, plots, isInJail, hasJailRescueCard, isbankrupt, playerPosition, inJailCount);
	}

}

void Monopoly::saveGame() {
	ofstream save;
	save.open("Save.txt");
	save << getTotalPlayers();
	for (int i = 0; i < getTotalPlayers(); i++) {
		save << board.getPlayerName(i) << " ";
		save << board.getPlayercash(i) << " ";
		save << board.getPlayerListSize(i) << " ";
		Property** temp = new Property * [board.getPlayerListSize(i)];
		temp = board.getPlayerList(i);
		for (int j = 0; j < board.getPlayerListSize(i); j++) {
			save << temp[i]->getPropertyID() << " ";
			save << temp[i]->getHouseCount() << " ";
			save << temp[i]->getShopCount() << " ";
			save << temp[i]->getHotelCount() << " ";
			save << temp[i]->getHasWifi() << " ";
			save << temp[i]->getHasGas() << " ";
			save << temp[i]->getHasElectricity() << " ";
		}
		save << board.getPlayerisInJail(i) << " ";
		save << board.getPlayerhasJailRescueCard(i) << " ";
		save << board.getPlayerisbankrupt(i) << " ";
		save << board.getPlayerplayerPosition(i) << " ";
		save << board.getPlayerinJailCount(i);
		if (i < getTotalPlayers() - 1) {
			save << endl;
		}
	}
}