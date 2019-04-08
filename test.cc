#include <iostream>
#include <string>
#include <curses.h>

using namespace std;

int main(int argc, char** argv)
{
	int i = 0;
	while(true) 
	{
		std::cout << "test" << i++ <<  std::endl;
		putchar('\r');
	}
}
