#include "Game.h"

Game game;
int main()
{
	SetWindowSize(900, 500);
	game.LoadingScreen();
	game.Menu();

	return 0;
}