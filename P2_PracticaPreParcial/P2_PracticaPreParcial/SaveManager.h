#pragma once

#include <iostream>
#include <Windows.h>

using namespace std;

template<typename T>
class SaveManager
{
private:
	static HANDLE hwnd;

public:
	static void LoadDefinitions(string definitions[]);
	static T LoadDataFile(string filePath);
	static void SaveDataFile(T data, string filePath);
};

#include "SaveManager.tpp"

