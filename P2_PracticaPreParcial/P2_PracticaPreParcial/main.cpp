#include <iostream>
#include <Windows.h>

#include "ConsoleHandler.h"
#include "Game.h"


using namespace std;


void main()
{
	//ConsoleHandler::SetConsoleSize();
	//ConsoleHandler::DrawFrame(0);

	Game game = Game();
	game.SaveData();
	game.DrawBoard();

}