#pragma once

#include "Vector2.h"

#include <iostream>
#include <Windows.h>

using namespace std;

struct Word
{
	string word;
	Vector2<int> position;
	bool wasDiscovered;
};

class Game
{
private:
	HANDLE hwnd;
	Word* wordsToGuess;
	string* definitions;
	int totalWords;
	int totalHits;
	Vector2<int> centerPos;
	Vector2<int> cursorPos;
	string centerWord;

	
	
	void DrawWord(Word word);

public:
	Game();
	~Game();

	void LoadData();
	void SaveData();
	void DrawBoard();
};

