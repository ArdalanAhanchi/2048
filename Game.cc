#include "Game.h"

#ifndef GAME_CC
#define GAME_CC

//Main constructor based on the gameSize (4 for a 4x4 game).
Game::Game(int gameSize)
{
  _gameSize = gameSize;
  _currentGame = new int*[_gameSize];
  for(int i = 0; i < _gameSize; i++)
    _currentGame[i] = new int[_gameSize];

  this->reset();
}

//Main destructor for deallocating _currentGame.
Game::~Game()
{
  for (int i = 0; i < _gameSize; i++)
    delete[] _currentGame[i];
}

//Move based on the passed char, (U,D,L,R) returns true if successful.
bool Game::move(char toMove)
{
  //Action based on the input.
  switch(toMove)
  {
    case 'u':   moveU();
                return true;

    case 'd':   moveD();
                return true;

    case 'l':   moveL();
                return true;

    case 'r':   moveR();
                return true;

    default:   return false;
  }

}

//Reset the game to all zeros.
void Game::reset()
{
  for(int i = 0; i < _gameSize; i++)
    for(int j = 0; j < _gameSize; j++)
      _currentGame[i][j] = 0;
}

//Returns true if the game is not finished.
bool Game::ended() const
{
	//Check every row and column, if there is a zero, return false.
	for(int r = 0; r < _gameSize; r++)
		for(int c = 0; c < _gameSize; c++)
			if(_currentGame[r][c] == 0) return false;

	//Check every row and column to see if there are any equal neighbors.
	for(int r = 0; r < _gameSize; r++)
		for(int c = 0; c < _gameSize; c++)
		{
			if( r < (_gameSize - 1) && _currentGame[r][c] == _currentGame[r + 1][c] ) return false;
			if( c < (_gameSize - 1) && _currentGame[r][c] == _currentGame[r][c + 1] ) return false;
		}

	return true;      //Else return true.
}

//Prints the current state of the game to provided function in a nice manner.
void Game::print(int (*printFunc)(const char* toPrint, ...)) const
{
	printFunc("\n");
	for(int i = 0; i < ( _gameSize + 1 ) * _gameSize * 2  ; i++)
	   printFunc("-");

	printFunc("\n");

	for(int row = 0; row < _gameSize; row++)
	{
        for(int col = 0; col < _gameSize; col++)
		{
            stringstream s;

			if(_currentGame[row][col] == 0)
				s << "| " << setw(_gameSize * 2) << " " ;
			else
    			s << "| " << setw(_gameSize * 2) << _currentGame[row][col] ;

            printFunc(s.str().c_str());
		}

        printFunc("|\n");

		for(int i = 0; i < _gameSize; i++)
        {
            stringstream s;
            s  << "| " << setw(_gameSize * 2) << " " ;
            printFunc(s.str().c_str());
        }

	    printFunc("|\n");

		for(int i = 0; i < ( _gameSize + 1 ) * _gameSize * 2 ; i++)
	         printFunc("-");

	    printFunc("\n");
	}
}

//Generate a random 2 or 4 at a random unoccupied location.
void Game::generateRandom()
{
  if(this->ended()) return;

  bool isValid = false;
  while(!isValid)
  {
    int row = rand() % _gameSize ;       //Generate a random row less than _gameSize.
    int col = rand() % _gameSize ;       //Generate a random col less than _gameSize.

    if(_currentGame[row][col] == 0)      //If the current block is not occupied...
    {
      _currentGame[row][col] = (rand() % 2 == 0 ? 2 : 4);   //Generate a random 2 or 4.
      isValid = true;
    }
  }
}

//Move Up.
void Game::moveU()
{
  int numOfMoves;
  do
  {
    numOfMoves = 0;
    for(int row = 1; row < _gameSize; row++)
    {
      for(int col = 0; col < _gameSize; col++)
      {
        if(_currentGame[row][col] == 0) continue;     //Skip if its empty.

        if(_currentGame[row][col] == _currentGame[row - 1][col])
        {
          _currentGame[row - 1][col] += _currentGame[row][col] + 1;
          _currentGame[row][col] = 0;
          numOfMoves++;
        }
        else
        if (_currentGame[row - 1][col] == 0)
        {
          _currentGame[row - 1][col] = _currentGame[row][col];
          _currentGame[row][col] = 0;
          numOfMoves++;
        }
      }
    }

  } while( numOfMoves != 0);

  resetMarked();

}

//Move Down.
void Game::moveD()
{
  int numOfMoves;
  do
  {
    numOfMoves = 0;
    for(int row = _gameSize - 2; row >= 0 ; row--)
    {
      for(int col = 0; col < _gameSize; col++)
      {
        if(_currentGame[row][col] == 0) continue;     //Skip if its empty.

        if(_currentGame[row][col] == _currentGame[row + 1][col])
        {
          _currentGame[row][col] += _currentGame[row + 1][col] + 1;
          _currentGame[row + 1][col] = 0;
          numOfMoves++;
        }
        else
        if (_currentGame[row + 1][col] == 0)
        {
          _currentGame[row + 1][col] = _currentGame[row][col];
          _currentGame[row][col] = 0;
          numOfMoves++;
        }
      }
    }

  } while( numOfMoves != 0);

  resetMarked();
}

//Move Left.
void Game::moveL()
{
  int numOfMoves;
  do
  {
    numOfMoves = 0;
    for(int col = 1; col < _gameSize; col++)
    {
      for(int row = 0; row < _gameSize; row++)
      {
        if(_currentGame[row][col] == 0) continue;     //Skip if its empty.

        if(_currentGame[row][col] == _currentGame[row][col - 1])
        {
          _currentGame[row][col - 1] += _currentGame[row][col] + 1;
          _currentGame[row][col] = 0;
          numOfMoves++;
        }
        else
        if (_currentGame[row][col - 1] == 0)
        {
          _currentGame[row][col - 1] = _currentGame[row][col];
          _currentGame[row][col] = 0;
          numOfMoves++;
        }
      }
    }
  } while( numOfMoves != 0);

  resetMarked();
}

//Move Right.
void Game::moveR()
{
  int numOfMoves;
  do
  {
    numOfMoves = 0;
    for(int row = 0; row < _gameSize; row++)
    {
      for(int col = _gameSize - 2; col >= 0; col--)
      {
        if(_currentGame[row][col] == 0) continue;     //Skip if its empty.

        if(_currentGame[row][col] == _currentGame[row][col + 1])
        {
          _currentGame[row][col + 1] += _currentGame[row][col] + 1;
          _currentGame[row][col] = 0;
          numOfMoves++;
        }
        else
        if (_currentGame[row][col + 1] == 0)
        {
          _currentGame[row][col + 1] = _currentGame[row][col];
          _currentGame[row][col] = 0;
          numOfMoves++;
        }
      }
    }

  } while( numOfMoves != 0);

  resetMarked();
}

//Reset the marked blocks (Reduce 1 from them).
void Game::resetMarked()
{
	for(int row = 0; row < _gameSize; row++)
		for(int col = 0; col < _gameSize; col++)
			if(_currentGame[row][col] % 2 != 0) _currentGame[row][col]-- ;
}

//Adds up all the blocks and returns an integer value.
int Game::score() const
{
	int toReturn = 0;
	for(int row = 0; row < _gameSize; row++)
		for(int col = 0; col < _gameSize; col++)
			toReturn += _currentGame[row][col];

	return toReturn;
}

//Returns a linear vector of blocks for AI training.
vector<int> Game::getData() const
{
	vector<int> toReturn;
	for(int row = 0; row < _gameSize; row++)
		for(int col = 0; col < _gameSize; col++)
			toReturn.push_back(_currentGame[row][col]);

	return toReturn;
}


#endif
