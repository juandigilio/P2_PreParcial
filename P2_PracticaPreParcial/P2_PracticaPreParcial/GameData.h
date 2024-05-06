#pragma once

#pragma once

#include "Vector2.h"

#include <iostream>

using namespace std;

const string gameDataPath = "../gameData.dat";
const string playerDataPath = "../playerData.dat";
const int totalWords = 5;


struct Word
{
	char word [15];
	int positionX;
	int positionY;
	bool wasDiscovered;
};

struct GameData
{
	Word wordsToGuess[totalWords];
};

struct PlayerData
{
	static const int MAX_NAME_LENGTH = 20;
	char name[MAX_NAME_LENGTH];
	int totalMissed;
};