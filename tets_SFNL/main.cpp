#include "stdafx.h"
#include "Game.h"

int WinMain()
{
	srand(time(NULL));
	Game game;
	game.run();
	return 0;
}