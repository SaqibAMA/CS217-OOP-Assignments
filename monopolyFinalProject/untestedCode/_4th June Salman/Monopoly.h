#include "Bank.h"
#include "Board.h"
#include "Property.h"
#include <SFML/Graphics.hpp>
#include <fstream>

struct Point {

	/*
	
	Point class to handle
	all board coordinates.

	*/

	int x;
	int y;

	Point() {
	
		x = 0;
		y = 0;

	}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void set(int x, int y) {
	
		this->x = x;
		this->y = y;

	}

};

class Monopoly
{
	Player* Playersarray;
	Property *PropertyAtThisSpace;
public:
	// Constructors
	Monopoly();

	// Getters and Setters
	void setTotalPlayers(int totalPlayers);
	int getTotalPlayers();


	// Member functions

	void printPlayerOnCell(sf::RenderWindow&,
		sf::RectangleShape,
		int, int);
	void initializePositions();
	int getPlayerPosition(int);

	void movePlayer(int, int, bool);

	void playDice(sf::RenderWindow&, sf::RectangleShape*,
		sf::Texture*);

	void updateDiceTextures(sf::Texture*);
	int convertFromCellToPropertyID(int);
	bool canBuildHouse(int,int);
	bool sameupgradedlevel(int, int);
	~Monopoly();

private:
	Bank bank;
	Board board;
	Point* bCoord;
	int* playerPosition;
	
};

