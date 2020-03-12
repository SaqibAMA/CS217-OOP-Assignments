#pragma once
class ticTacToe
{
private:

	// 2D array of board
	int** board;

	// Size of board
	int n;

	// Keeps track if the game has been won, lost or drawn.
	// 0 - Drawn, 1 - Won by X, -1 Won by 0
	int boardState;


public:
	ticTacToe();
	ticTacToe(int _n);
	bool isWon();
	void print();
	~ticTacToe();
};

