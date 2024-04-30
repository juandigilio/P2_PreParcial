#ifndef VECTOR2_TPP
#define VECTOR2_TPP

#include "Vector2.h"

#include <iostream>

template<typename T>
inline Vector2<T>::Vector2()
{
}

template<typename T>
inline Vector2<T>::Vector2(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<typename T>
inline Vector2<T> Vector2<T>::operator+(Vector2 other)
{
	return Vector2(this->x + other.x, this->y + other.y);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator-(Vector2 other)
{
	return Vector2(this->x - other.x, this->y - other.y);
}

template<typename T>
inline std::string Vector2<T>::ToString()
{
	return "(" + to_string(x) + ", " + to_string(y) + ")";
}

#endif