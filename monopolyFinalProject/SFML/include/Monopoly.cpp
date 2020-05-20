#include "Monopoly.h"


Monopoly::Monopoly() {

	totalPlayers = 0;

	/*
	
	row 1 Y: 650px;

	*/

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


	fin.close();


}

// Getters and Setters

void Monopoly::setTotalPlayers(int totalPlayers) {


	if (totalPlayers > 0)
		this->totalPlayers = totalPlayers;


}

int Monopoly::getTotalPlayers() {

	return totalPlayers;

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

// Destructor

Monopoly::~Monopoly() {

	totalPlayers = 0;

}