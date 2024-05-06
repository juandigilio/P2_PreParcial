#pragma once

#pragma once

#include "Vector2.h"

#include <iostream>

using namespace std;

const string gameDataPath = "../gameData.dat";
const string playerDataPath = "../playerData.dat";
const int totalWords = 5;
const int maxLength = 10;

struct Word
{
	char word [maxLength];
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