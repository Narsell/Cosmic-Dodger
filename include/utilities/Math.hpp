#pragma once
#include <iostream>

class Vector2 {

public:

	static Vector2 ZERO;
	static Vector2 RIGHT;
	static Vector2 LEFT;
	static Vector2 UP;
	static Vector2 DOWN;

	float x, y;

	Vector2();

	Vector2(float xy);

	Vector2(float p_x, float p_y);

	const float Lenght() const;

	const float Dot(const Vector2& other) const;

	const float AngleTo(const Vector2& other) const;

	const Vector2 Normalized() const;

	const Vector2 RotatedBy(const float angle) const;

	const Vector2 operator+(const Vector2& other) const;
	const Vector2 operator-(const Vector2& other) const;
	const Vector2 operator/(float scalar) const;
	const Vector2 operator*(float scalar) const;

	void operator+=(const Vector2& other);
	void operator-=(const Vector2& other);
	void operator*=(float scalar);

	void Print() const;

};

//TODO namespace?
class Math {

public:
	//Returns a random integer withtin the range
	static const int RandomRange(const int from, const int to);
	//Determines if two floats are nearly equal (by some epsilon)
	static const bool IsNearlyEqual(const float x, const float b);
	//Radians to Degrees conversion.
	static const float RadiansToDegrees(const float radians);
	//Degrees to Radians conversion.
	static const float DegreesToRadians(const float radians);
	//Gets a Vector2 direction from a given angle (degrees).
	static const Vector2 GetDirectionFromAngle(const float angle);
	//Gets an angle (degrees) in degs from a given Vector2 direction.
	static const float GetAngleFromDirection(const Vector2& direction);
	//Moves a vector a towards a target vector by a factor of f
	static const Vector2 Lerp(const Vector2& a, const Vector2& target, const float f=0.5f);
};


