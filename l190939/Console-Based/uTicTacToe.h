#pragma once
#include "ticTacToe.h"

class uTicTacToe
{
private:

	// 2D Array of games
	ticTacToe game[3][3];

	// 4D Array of boards
	// that keeps the actual
	// board contents
	int**** boardArray;

	// 2D array of board states
	// used for determining
	// if the game has been won
	int** boardStates;

	// grid size
	int n;

	// Keeps the current turn
	int turn;

	// Keeps the move count
	int mvCount;


	// Keeps track of the board
	// that is currently enabled
	int enI;	// y coord
	int enJ;	// x coord


	// Boolean to keep a track
	// of game state
	bool gameWon;
	
public:

	// Default constructor
	uTicTacToe();

	bool isWon();

	void setGlobalTurn();
	void updateBoardStates();

	void print();
	void printBoardAtLocation(int** boardArray, int yAlign, int xAlign);

	int getRow();
	int getCol();

	int getBoardRow();
	int getBoardCol();

	bool canMove(int eI, int eJ, int i, int j);
	void makeMove(int i, int j, bool u);

	bool isDraw();

	void saveGame();
	void loadGame();

	~uTicTacToe();
};

