#include "ConsoleHandler.h"

#include <iostream>


using namespace std;

COORD ConsoleHandler::consoleSize = {90, 40};
COORD ConsoleHandler::cursorPosition = { 0, 0 };
HANDLE ConsoleHandler::hwnd{};

void ConsoleHandler::SetConsoleSize()
{
	/*do 
	{
		system("cls");

		cout << "Ingrese el ancho para la consola (min 40, max 90): ";
		cin >> consoleSize.X;

		if (consoleSize.X < 40)
		{

		}
		else if (consoleSize.X > 90)
		{

		}

	} while (consoleSize.X < 40 || consoleSize.X > 90);

	do
	{
		system("cls");

		cout << "Ingrese el alto para la consola (min 30, max 40): ";
		cin >> consoleSize.Y;

		if (consoleSize.Y < 30)
		{
			
		}
		else if (consoleSize.Y > 40)
		{

		}

	} while (consoleSize.Y < 30 || consoleSize.Y > 40);
	*/

	SMALL_RECT rect;

	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = consoleSize.Y - 1;
	rect.Right = consoleSize.X - 1;

	hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(hwnd, consoleSize);
	SetConsoleWindowInfo(hwnd, TRUE, &rect);

	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	cci.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void ConsoleHandler::DrawFrame(int delay)
{
	consoleSize.X = 90;
	consoleSize.Y = 40;

	system("cls");

	cout << (char)201;

	for (int i = 0; i < (consoleSize.X - 2); i++)
	{
		cout << (char)205;

		Sleep(delay);
	}

	cout << (char)187;

	cursorPosition.X = consoleSize.X - 1;
	cursorPosition.Y = 1;

	for (int i = 0; i < (consoleSize.Y - 2); i++)
	{
		SetConsoleCursorPosition(hwnd, cursorPosition);
		cout << (char)186;
		cursorPosition.Y++;
		if (delay > 0)
		{
			Sleep(delay + 20);
		}
	}

	SetConsoleCursorPosition(hwnd, cursorPosition);

	cout << (char)188;

	cursorPosition.X--;
	SetConsoleCursorPosition(hwnd, cursorPosition);

	for (int i = 0; i < (consoleSize.X - 2); i++)
	{
		cout << (char)205;
		cursorPosition.X--;
		SetConsoleCursorPosition(hwnd, cursorPosition);
		Sleep(delay);
	}

	SetConsoleCursorPosition(hwnd, cursorPosition);

	cout << (char)200;

	cursorPosition.Y--;
	SetConsoleCursorPosition(hwnd, cursorPosition);

	for (int i = 0; i < (consoleSize.Y - 2); i++)
	{
		cout << (char)186 << endl;
		cursorPosition.Y--;
		SetConsoleCursorPosition(hwnd, cursorPosition);
		if (delay > 0)
		{
			Sleep(delay + 20);
		}
	}

	string imageCampus = "Digital Happines";

	cursorPosition.X = (consoleSize.X / 2) - (imageCampus.length() / 2) - 1;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(hwnd, cursorPosition);

	for (int i = 0; i < imageCampus.length(); i++)
	{
		cout << imageCampus[i];
		if (delay > 0)
		{
			Sleep(100);
		}
	}
	cout << (char)169;
}

HANDLE ConsoleHandler::GetHandle()
{
	return hwnd;
}

Vector2<int> ConsoleHandler::GetConsoleSize()
{
	return Vector2<int>(consoleSize.X, consoleSize.Y);
}
