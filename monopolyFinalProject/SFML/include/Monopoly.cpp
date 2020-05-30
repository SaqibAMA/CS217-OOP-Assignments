#include "Monopoly.h"


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


	fin.close();


}

// Getters and Setters

void Monopoly::setTotalPlayers(int totalPlayers) {


	board.setPlayerCount(totalPlayers);
	board.allocatePrevTurns();

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


void Monopoly::initializePositions() {


	playerPosition = new int[board.getPlayerCount()];

	for (int i = 0; i < board.getPlayerCount(); i++) {
		playerPosition[i] = 0;
	}


}

int Monopoly::getPlayerPosition(int playerID) {

	return playerPosition[playerID];

}

void Monopoly::movePlayer(int playerID) {

	playerPosition[playerID]++;
	playerPosition[playerID] %= 40;

}

void Monopoly::playDice(sf::RenderWindow& window,
	sf::RectangleShape* dice, sf::Texture* diceTexture) {


	const char* diceTextureImg[6] =
	{
		"assets/dice_1.png",
		"assets/dice_2.png",
		"assets/dice_3.png",
		"assets/dice_4.png",
		"assets/dice_5.png",
		"assets/dice_6.png"

	};


	int* diceNum = board.rollDice();

	if (diceNum[0] > 0 && diceNum[1] > 0) {

		diceTexture[0].loadFromFile(diceTextureImg[diceNum[0] - 1]);
		diceTexture[1].loadFromFile(diceTextureImg[diceNum[1] - 1]);


	
	}
	else {
	
		

	}

}


// Destructor

Monopoly::~Monopoly() {


}