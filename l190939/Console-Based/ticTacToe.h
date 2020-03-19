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


	// Keeps the record of current turn.
	int turn;


	// Keeps the current movec count.
	int mvCount;


public:

	// Deafault and parameterized
	// constructors
	ticTacToe();
	ticTacToe(int _n);

	// Returns if the game has been won
	bool isWon();

	// Returns if the game has been drawn
	bool isDraw();

	// Prints the board on the screen
	void print();


	// Saves the game into Game.txt
	void saveGame();

	// Loads the game from Game.txt
	void loadGame();

	// Manages the row input
	int getRow();

	// Manages the column input
	int getCol();


	// Additional function to
	// return the current board
	int** getBoard();

	// Additional function to
	// return the board state
	int getBoardState();

	// Sets the turn of the board, externally
	void setTurn(int t);


	// Checks if the move was valid
	bool canMove(int i, int j);

	// Makes the move, if it is valid
	// Also checks for win or draw
	void makeMove(int i, int j, bool u);

	// Destructor
	~ticTacToe();
};

