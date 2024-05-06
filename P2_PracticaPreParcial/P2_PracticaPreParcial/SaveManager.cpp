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

	inputStream.open("../definitions.txt");

	Vector2<int> centerPos;
	centerPos.x = ConsoleHandler::GetConsoleSize().x / 2;
	centerPos.y = (ConsoleHandler::GetConsoleSize().y / 2);

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

		cout << "Definitions loaded OK" << endl;
	}
	else
	{
		cout << "No se pudo cargar definitons" << endl;
		//throw error
	}
	inputStream.close();
}

template<typename T>
T SaveManager<T>::LoadDataFile(string filePath)
{
	T data = T();

	ifstream binaryInput = ifstream();

	try
	{
		cout << "Reading from the data file..." << endl;

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