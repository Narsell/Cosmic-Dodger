#pragma once
#include <iostream>

class Vector2 {

public:

	static Vector2 ZERO;

	float x, y;

	Vector2();

	Vector2(float xy);

	Vector2(float p_x, float p_y);

	void operator +=(const Vector2& deltaVector);

	void Print() const;

};



