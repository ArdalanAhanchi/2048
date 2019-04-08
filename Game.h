#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <sstream>

#ifndef GAME_H
#define GAME_H

using namespace std;

class Game
{
public:

	//Main constructor based on the GameSize (4 for a 4x4 Game).
	Game(int GameSize);

	//Main destructor for deallocating _currentGame.
	~Game();

	//Move based on the passed char, (U,D,L,R) returns true if successful.
	bool move(char toMove);

	//Reset the Game to all zeros.
	void reset();

	//Returns true if the Game is not finished.
	bool ended() const;

	/*
	//Prints the current state of the Game to cout in a nice manner.
	void print() const;
	*/

	//Prints the current state of the game to provided function in a nice manner.
	void print(int (*printFunc)(const char* toPrint, ...) = printf) const;

	//Adds up all the blocks and returns an integer value.
	int score() const;

	//Returns a linear vector of blocks for AI training.
	vector<int> getData() const;

	//Generate a random 2 or 4 at a random unoccupied location.
	void generateRandom();

private:

	int** _currentGame;           //Two dimentional array for holding the Game data.
	int _gameSize;                //integer for holding the Game dimentions (_GameSize x _GameSize).

	//Move Up.
	void moveU();

	//Move Down.
	void moveD();

	//Move Left.
	void moveL();

	//Move Right.
	void moveR();

	//Reset the marked blocks (Reduce 1 from them).
	void resetMarked();

};

#endif
