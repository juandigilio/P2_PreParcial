#pragma once

#include "Vector2.h"
#include "GameData.h"

#include <iostream>
#include <Windows.h>

using namespace std;

class Game
{
private:
	HANDLE hwnd;
	Vector2<int> centerPos;
	Vector2<int> cursorPos;
	string centerWord;
	string definitions[totalWords];

	GameData gameData;
	PlayerData playerData;

	void SetConsoleConfiguration();
	void InitGame();
	void LoadSave();
	void DrawBoard();
	void DrawDefinitions();
	void GetInput();
	void GameLoop();
	void SetCursorPos(Vector2<int> pos);
	void SetCursorPos(Word word);

public:
	Game();
	~Game();

	void RunGame();
};

