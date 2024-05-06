#include <iostream>
#include <Windows.h>

#include "ConsoleHandler.h"
#include "GameData.h"
#include "SaveManager.h"
#include "Game.h"


using namespace std;


void main()
{
	Game game = Game();
	game.RunGame();

}