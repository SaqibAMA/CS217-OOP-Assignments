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

void Monopoly::movePlayer(int playerID, int currRollCount, bool toJail = false) {


	//cout << "\nMoving from " << playerPosition[playerID];

	playerPosition[playerID] += currRollCount;
	playerPosition[playerID] %= 40;

	if (toJail) playerPosition[playerID] = 10;

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