#include"Game.h"
#include<time.h>
#include <string.h>
using namespace time;

int main()
{
	srand(time(static_cast<unsigned>(0)));

	Game game;

	game.run();



	//End of app
	return 0;
}