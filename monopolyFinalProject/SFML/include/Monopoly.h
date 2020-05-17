
#pragma once

#include <Bank.h>
#include <Board.h>

class Monopoly
{

public:
	// Constructors
	Monopoly();

	// Getters and Setters
	void setTotalPlayers(int totalPlayers);
	int getTotalPlayers();

	~Monopoly();

private:
	Bank bank;
	Board board;
	int totalPlayers;

};

