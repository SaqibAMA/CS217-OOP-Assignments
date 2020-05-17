#include "Monopoly.h"

Monopoly::Monopoly() {

	totalPlayers = 0;

}



// Getters and Setters

void Monopoly::setTotalPlayers(int totalPlayers) {


	if (totalPlayers > 0)
		this->totalPlayers = totalPlayers;


}

int Monopoly::getTotalPlayers() {

	return totalPlayers;

}


// Destructor

Monopoly::~Monopoly() {

	totalPlayers = 0;

}