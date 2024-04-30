#pragma once

#include <iostream>

template <typename T>

class Vector2
{
public:

	T x;
	T y;

	Vector2();
	Vector2(T x, T y);

	Vector2 operator + (Vector2 other);
	Vector2 operator - (Vector2 other);

	std::string ToString();
};

#include "Vector2.tpp"

