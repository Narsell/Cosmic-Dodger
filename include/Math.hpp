#pragma once
#include <iostream>

class Vector2 {

public:

	int x, y;

	Vector2();

	Vector2(int xy);

	Vector2(int p_x, int p_y);

	const Vector2& operator+(const Vector2& other);
	void operator+=(const Vector2& other);

	const Vector2& operator-(const Vector2& other);
	void operator-=(const Vector2& other);

	const Vector2& operator*(const float scalar);
	void operator*=(const float scalar);

	void Print() const;

	// STATICS

	static Vector2 ZERO;
	static Vector2 RIGHT;
	static Vector2 LEFT;
	static Vector2 UP;
	static Vector2 DOWN;

};



