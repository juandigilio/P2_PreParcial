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

	GameData* gameData;
	PlayerData* playerData;

	
	void SetCursorPos(Vector2<int> pos);
	void SetCursorPos(Word word);
	void LoadSave(GameData& gameData, PlayerData& playerData);

public:
	Game(GameData& gameData, PlayerData& playerData);
	~Game();

	void DrawBoard(GameData& gameData);
	void DrawDefinitions();
};

