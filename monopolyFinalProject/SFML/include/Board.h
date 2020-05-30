#pragma once
class Board
{

private:
	int** prevTurns;
	int playerCount;

public:
	Board();

	int getPlayerCount();
	void setPlayerCount(int);

	void allocatePrevTurns();
	int** getPrevTurns();

	~Board();
};