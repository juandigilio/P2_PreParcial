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
	static Vector2<int> centerPos;
	static void SetFontSize(int width, int height);
	static void SetConsoleSize();
	static void DrawFrame(int delay);
	static HANDLE GetHandle();
	static Vector2<int> GetConsoleSize();
};

