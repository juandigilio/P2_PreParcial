#include <iostream>
#include <Windows.h>

#include "ConsoleHandler.h"
#include "GameData.h"
#include "SaveManager.h"
#include "Game.h"


using namespace std;


void main()
{
	ConsoleHandler::SetFontSize(20, 25);
	ConsoleHandler::SetConsoleSize();
	ConsoleHandler::DrawFrame(0);

	GameData gameData{};
	PlayerData playerData{};

	Game game = Game(gameData, playerData);
	game.DrawDefinitions();
	//game.DrawBoard(gameData);

}