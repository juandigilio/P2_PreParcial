#ifndef SAVEMANAGER_TPP
#define SAVEMANAGER_TPP

#include "SaveManager.h"

#include "GameData.h"
#include "ConsoleHandler.h"
#include "Vector2.h"
#include <fstream>

HANDLE SaveManager<GameData>::hwnd{};


template<typename T>
void SaveManager<T>::LoadDefinitions(string definitions[])
{
	hwnd = ConsoleHandler::GetHandle();
	const int bufferSize = 128;

	ifstream inputStream = ifstream();

	Vector2<int> centerPos;
	centerPos.x = ConsoleHandler::GetConsoleSize().x / 2;
	centerPos.y = (ConsoleHandler::GetConsoleSize().y / 2);

	string confirm = "Definitions loaded OK";
	string error = "The file could not be opened";
	string reading = "Reading from the data file...";

	try
	{
		centerPos.x -= reading.length() / 2;
		ConsoleHandler::SetCursorPos(centerPos);
		cout << reading << endl;

		inputStream.open("../definitions.txt");

		if (!inputStream.good())
		{
			centerPos.x = ConsoleHandler::GetConsoleSize().x / 2 - error.length() / 2;
			centerPos.y++;
			ConsoleHandler::SetCursorPos(centerPos);

			throw ofstream::failure(error);
		}		
		else
		{
			centerPos.x = ConsoleHandler::GetConsoleSize().x / 2 - confirm.length() / 2;
			centerPos.y++;
			ConsoleHandler::SetCursorPos(centerPos);
			cout << confirm;

			int i = 0;
			while (!inputStream.eof())
			{
				char tempText[bufferSize];

				inputStream.getline(tempText, bufferSize);

				definitions[i] = tempText;
				i++;
			}
		}

		Sleep(2000);

		inputStream.close();
	}
	catch (const ifstream::failure& exception)
	{
		cerr << "INPUT FILE STREAM ERROR: " << exception.what() << endl;

		if (inputStream.is_open())
		{
			inputStream.close();
		}
	}
}

template<typename T>
T SaveManager<T>::LoadDataFile(string filePath)
{
	T data = T();
	ifstream binaryInput = ifstream();

	string reading = "Reading from the data file...";

	Vector2<int> newPos;
	newPos.x = ConsoleHandler::GetConsoleSize().x / 2 - reading.length();
	newPos.y = (ConsoleHandler::GetConsoleSize().y / 2) + 2;

	try
	{
		newPos.x = ConsoleHandler::GetConsoleSize().x / 2 - reading.length();
		newPos.y = (ConsoleHandler::GetConsoleSize().y / 2) + 2;
		cout << reading << endl;

		binaryInput.open(filePath, ios::in | ios::binary);

		if (!binaryInput.is_open())
		{
			throw ofstream::failure("The file could not be opened");
		}

		binaryInput.read(reinterpret_cast<char*>(&data), sizeof(T));

		if (binaryInput.fail())
		{
			throw ofstream::failure("The file could not be read correctly");
		}

		binaryInput.close();

		if (binaryInput.is_open())
		{
			throw ofstream::failure("The file could not be closed");
		}
	}
	catch (const ifstream::failure& exception)
	{
		cerr << "INPUT FILE STREAM ERROR: " << exception.what() << endl;

		if (binaryInput.is_open())
		{
			binaryInput.close();
		}
	}

	return data;
}

template<typename T>
void SaveManager<T>::SaveDataFile(T data, string filePath)
{
	ofstream outputStream = ofstream();

	try
	{
		cout << "Writing to the data file..." << endl;

		outputStream.open(filePath, ios::out | ios::binary);

		if (!outputStream.is_open())
		{
			throw ofstream::failure("The file could not be opened");
		}

		outputStream.write(reinterpret_cast<char*>(&data), sizeof(T));

		if (outputStream.fail())
		{
			throw ofstream::failure("The file could not be written correctly");
		}

		outputStream.close();

		if (outputStream.is_open())
		{
			throw ofstream::failure("The file could not be closed");
		}
	}
	catch (const ofstream::failure& exception)
	{
		cerr << "OUTPUT FILE STREAM ERROR: " << exception.what() << endl;

		if (outputStream.is_open())
		{
			outputStream.close();
		}
	}
}

#endif