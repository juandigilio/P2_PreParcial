#pragma once

#include "Vector2.h"

#include <windows.h>

class ConsoleHandler
{
private:
	static COORD consoleSize;
	static COORD cursorPosition;
	static HANDLE hwnd;

public:
	static void SetConsoleSize();
	static void DrawFrame(int delay);
	static HANDLE GetHandle();
	static Vector2<int> GetConsoleSize();
};

