#include "Game.h"

#include "ConsoleHandler.h"
#include "SaveManager.h"

#include <fstream>
#include <conio.h>

Game::Game()
{
}

Game::~Game()
{
	SaveManager<GameData>::SaveDataFile(gameData, gameDataPath);
	SaveManager<PlayerData>::SaveDataFile(playerData, playerDataPath);
}

void Game::RunGame()
{
	gameData = GameData();
	playerData = PlayerData();

	SetConsoleConfiguration();
	InitGame();
	LoadSave();

	DrawDefinitions();

	//gameData.wordsToGuess[0].wasDiscovered = true;
	//gameData.wordsToGuess[1].wasDiscovered = true;
	//gameData.wordsToGuess[2].wasDiscovered = true;

	DrawBoard();

	GameLoop();
}

void Game::SetConsoleConfiguration()
{
	ConsoleHandler::SetFontSize(20, 25);
	ConsoleHandler::SetConsoleSize();
	ConsoleHandler::DrawFrame(0);
}

void Game::InitGame()
{
	hwnd = ConsoleHandler::GetHandle();

	this->centerPos = ConsoleHandler::centerPos;

	string words[totalWords];
	words[0] = "AJO.";
	words[1] = "CUBO.";
	words[2] = "MAGIA.";
	words[3] = "ROTO.";
	words[4] = "MAESTRO.";

	for (int i = 0; i < totalWords; i++)
	{
		for (int j = 0; j < words[i].length(); j++)
		{
			if (j >= maxLength)
			{
				break;
			}
			gameData.wordsToGuess[i].word[j] = words[i][j];
		}

		gameData.wordsToGuess[i].wasDiscovered = false;
	}

	gameData.wordsToGuess[0].positionX = centerPos.x - 1;
	gameData.wordsToGuess[0].positionY = centerPos.y;

	gameData.wordsToGuess[1].positionX = centerPos.x - 1;
	gameData.wordsToGuess[1].positionY = centerPos.y + 1;

	gameData.wordsToGuess[2].positionX = centerPos.x - 2;
	gameData.wordsToGuess[2].positionY = centerPos.y + 2;

	gameData.wordsToGuess[3].positionX = centerPos.x - 1;
	gameData.wordsToGuess[3].positionY = centerPos.y + 3;

	gameData.wordsToGuess[4].positionX = centerPos.x - 3;
	gameData.wordsToGuess[4].positionY = centerPos.y + 4;

	centerWord = "JUGOS";

	SaveManager<GameData>::LoadDefinitions(definitions);
}

void Game::LoadSave()
{
	string question = "Load saved game? : Y/N";
	string newGame = "New game created, press any key to continue...";
	char input{};

	system("cls");
	ConsoleHandler::DrawFrame(0);

	cursorPos = { centerPos.x, centerPos.y };

	ifstream binaryInput = ifstream();
	binaryInput.open(gameDataPath, ios::in | ios::binary);

	if (binaryInput.is_open())
	{
		cursorPos.x -= question.length() / 2;
		SetCursorPos(cursorPos);

		cout << question;

		do
		{
			input = toupper(_getch());

		} while (input != 'Y' && input != 'N');

		if (input == 'Y')
		{
			gameData = SaveManager<GameData>::LoadDataFile(gameDataPath);
			playerData = SaveManager<PlayerData>::LoadDataFile(playerDataPath);
		}
		else
		{
			cursorPos = centerPos;
			cursorPos.y++;
			cursorPos.x -= newGame.length() / 2;
			SetCursorPos(cursorPos);
			cout << newGame;
		}
	}
	else
	{
		cursorPos.x -= newGame.length() / 2;
		SetCursorPos(cursorPos);
		cout << newGame;
	}

	char key = _getch();
}

void Game::DrawBoard()
{
	for (int i = 0; i < totalWords; i++)
	{
		Vector2<int> newPos{ gameData.wordsToGuess[i].positionX, gameData.wordsToGuess[i].positionY };
		SetCursorPos(newPos);

		int j = 0;

		while (gameData.wordsToGuess[i].word[j] != '.')
		{
			if (!gameData.wordsToGuess[i].wasDiscovered)
			{
				cout << "_";
			}
			else
			{
				cout << gameData.wordsToGuess[i].word[j];
			}

			j++;
		}
	}

	Vector2<int> newPos{ centerPos.x , centerPos.y };

	for (int i = 0; i < centerWord.length(); i++)
	{
		SetCursorPos(newPos);

		cout << centerWord[i];

		newPos.y++;
	}
}

void Game::DrawDefinitions()
{
	Vector2<int> newPos{ 1, 2 };

	system("cls");

	ConsoleHandler::DrawFrame(0);

	for (int i = 0; i < totalWords; i++)
	{
		int j = 0;

		SetCursorPos(newPos);

		while (definitions[i][j] != '.')
		{
			cout << definitions[i][j];
			j++;
		}

		newPos.y++;
	}
}

void Game::GetInput()
{
	string numberQuest = "En que posicion desea escribir? (0 == EXIT): ";
	string wordQuest = "Ingrese la palabra: ";
	string clean = "                                       ";
	Vector2<int> questPos{ 2, ConsoleHandler::GetConsoleSize().y - 2 };
	bool keepPlaying = true;
	int questInput = -1;
	char word[10];

	while (keepPlaying)
	{
		SetCursorPos(questPos);
		cout << numberQuest;

		bool isValid = false;

		do
		{
			Vector2<int> newPos = questPos;
			newPos.x += numberQuest.length();
			SetCursorPos(newPos);
			cin >> questInput;

			isValid = questInput == 0 || questInput == 1 || questInput == 2 || questInput == 3 || questInput == 4 || questInput == 5;

		} while (!isValid);
		
		if (questInput != 0)
		{

		}
		else
		{
			keepPlaying = false;
		}
	}

	
}

void Game::GameLoop()
{

}

void Game::SetCursorPos(Vector2<int> pos)
{
	COORD actualPos{ pos.x, pos.y };

	SetConsoleCursorPosition(hwnd, actualPos);
}

void Game::SetCursorPos(Word word)
{
	COORD actualPos{ word.positionX, word.positionY };

	SetConsoleCursorPosition(hwnd, actualPos);
}

