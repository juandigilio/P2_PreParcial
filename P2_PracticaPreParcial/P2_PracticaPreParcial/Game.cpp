#include "Game.h"

#include "ConsoleHandler.h"
#include <fstream>

Game::Game()
{
	hwnd = ConsoleHandler::GetHandle();
	totalWords = 5;

	centerPos.x = ConsoleHandler::GetConsoleSize().x / 2;
	centerPos.y = (ConsoleHandler::GetConsoleSize().y / 2) - (totalWords / 2);

	wordsToGuess = new Word[totalWords];
	definitions = new string[totalWords];
	
	wordsToGuess[0].word = "ajo";
	wordsToGuess[0].position.x = centerPos.x - 1;
	wordsToGuess[0].position.y = centerPos.y;

	wordsToGuess[1].word = "cubo";
	wordsToGuess[1].position.x = centerPos.x - 1;
	wordsToGuess[1].position.y = centerPos.y + 1;

	wordsToGuess[2].word = "magia";
	wordsToGuess[2].position.x = centerPos.x - 2;
	wordsToGuess[2].position.y = centerPos.y + 2;

	wordsToGuess[3].word = "roto";
	wordsToGuess[3].position.x = centerPos.x - 1;
	wordsToGuess[3].position.y = centerPos.y + 3;

	wordsToGuess[4].word = "maestro";
	wordsToGuess[4].position.x = centerPos.x - 3;
	wordsToGuess[4].position.y = centerPos.y + 4;

	for (int i = 0; i < totalWords; i++)
	{
		wordsToGuess[i].wasDiscovered = false;
	}

	centerWord = "JUGOS";

	//LoadData();
}

Game::~Game()
{
	delete[] wordsToGuess;
	delete[] definitions;
}

void Game::LoadData()
{
	const int bufferSize = 128;

	ifstream inputStream = ifstream();

	inputStream.open("../definitions.txt");

	if (inputStream.good())
	{
		int i = 0;
		while (!inputStream.eof())
		{
			char tempText[bufferSize];

			inputStream.getline(tempText, bufferSize);

			definitions[i] = tempText;
			i++;
		}
	}
	else
	{
		cout << "No se pudo cargar definitons" << endl;
		//throw error
	}
	inputStream.close();

	ifstream binariInput("../gameSave.bin", std::ios::binary);

	if (binariInput.is_open())
	{
		binariInput.read(reinterpret_cast<char*>(&totalWords), sizeof(int));

		wordsToGuess = new Word[totalWords];
		definitions = new std::string[totalWords];

		for (int i = 0; i < totalWords; i++)
		{
			int wordLength;
			binariInput.read(reinterpret_cast<char*>(&wordLength), sizeof(int));

			char* buffer = new char[wordLength + 1];
			binariInput.read(buffer, wordLength);
			buffer[wordLength] = '\0';
			wordsToGuess[i].word = std::string(buffer);
			delete[] buffer;

			binariInput.read(reinterpret_cast<char*>(&wordsToGuess[i].position), sizeof(int));

			binariInput.read(reinterpret_cast<char*>(&wordsToGuess[i].wasDiscovered), sizeof(bool));
		}

		binariInput.close();

		std::cout << "Binari loaded!" << std::endl;
	}
	else
	{
		std::cerr << "Binari error!" << std::endl;
	}
}

void Game::SaveData()
{
	ofstream outputStream("../gameSave.bin", std::ios::binary);

	if (outputStream.is_open())
	{
		outputStream.write(reinterpret_cast<char*>(&totalWords), sizeof(int));
		
		for (int i = 0; i < totalWords; i++)
		{			
			int wordLength = wordsToGuess[i].word.length();
			outputStream.write(reinterpret_cast<char*>(&wordLength), sizeof(int));
			
			outputStream.write(wordsToGuess[i].word.c_str(), wordLength);
			
			outputStream.write(reinterpret_cast<char*>(&wordsToGuess[i].position), sizeof(int));

			outputStream.write(reinterpret_cast<char*>(&wordsToGuess[i].wasDiscovered), sizeof(bool));
		}

		outputStream.close();

		std::cout << "Game saved!" << std::endl;
	}
	else
	{
		std::cerr << "Save error!" << std::endl;
	}
}

void Game::DrawBoard()
{
	COORD actualPos;

	for (int i = 0; i < totalWords; i++)
	{
		actualPos.X = wordsToGuess[i].position.x;
		actualPos.Y = wordsToGuess[i].position.y;
		SetConsoleCursorPosition(hwnd, actualPos);

		for (int j = 0; j < wordsToGuess[i].word.length(); j++)
		{
			if (!wordsToGuess[i].wasDiscovered)
			{
				cout << "_";
			}
			else
			{
				cout << wordsToGuess[i].word[j];
			}
		}
	}

	actualPos.X = centerPos.x;
	actualPos.Y = centerPos.y;

	for (int i = 0; i < centerWord.length(); i++)
	{
		SetConsoleCursorPosition(hwnd, actualPos);

		cout << centerWord[i];

		actualPos.Y++;
	}
}

void Game::DrawWord(Word word)
{
}

