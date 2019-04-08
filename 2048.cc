#include "Game.h"
#include "stdlib.h"
#include <string>
#include <ncurses.h>

using namespace std;

int main(int argc, char** argv)
{
	int size = 4;									//Default Size.
	if(argc == 2) 									//Get size if there are arguments.
		size = stoi(argv[argc - 1]);

	initscr();										// Start curses mode
	Game newGame(size);
	newGame.generateRandom();
	printw("Press any button to start...");

	while(!newGame.ended())
	{
		refresh();
		noecho();
		char nextMove = getch();
		clear();

		if(nextMove)

		switch(nextMove)
		{
			case 'a':
				newGame.move('l');
				newGame.generateRandom();
				break;

			case 'd':
				newGame.move('r');
				newGame.generateRandom();
				break;

			case 'w':
				newGame.move('u');
				newGame.generateRandom();
				break;

			case 's':
				newGame.move('d');
				newGame.generateRandom();
				break;

			case 'x':
				endwin();
				cout << "Exiting Game." << endl;
				return 0;

			default:
				break;
		}

		clear();
		printw("Score: %i \n" , newGame.score());
		newGame.print(printw);
		printw("\nEnter Next Move (W-A-S-D): ");
	}

	endwin();
	cout << "Game Over" << endl;

	return 0;
}
