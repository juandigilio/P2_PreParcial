#include "ConsoleHandler.h"

#include <iostream>


using namespace std;

COORD ConsoleHandler::consoleSize = {35, 25};
COORD ConsoleHandler::cursorPosition = { 0, 0 };
HANDLE ConsoleHandler::hwnd{};
Vector2<int> ConsoleHandler::centerPos{};

void ConsoleHandler::SetFontSize(int width, int height)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;

	cfi.dwFontSize.X = width;
	cfi.dwFontSize.Y = height;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void ConsoleHandler::SetConsoleSize()
{
	do 
	{
		system("cls");

		cout << "Ingrese el ancho para la consola (min 50, max 70): ";
		cin >> consoleSize.X;

	} while (consoleSize.X < 50 || consoleSize.X > 70);

	do
	{
		system("cls");

		cout << "Ingrese el alto para la consola (min 15, max 25): ";
		cin >> consoleSize.Y;

	} while (consoleSize.Y < 15 || consoleSize.Y > 25);

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

	centerPos.x = consoleSize.X / 2;
	centerPos.y = (consoleSize.Y / 2);
}

void ConsoleHandler::DrawFrame(int delay)
{
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
