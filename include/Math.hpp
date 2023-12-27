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

	const double Lenght() const;

	const float Dot(const Vector2& other) const;

	const double AngleTo(const Vector2& other) const;

	const Vector2 Normalized() const;

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
	//Determines if two floats are nearly equal (by some epsilon)
	static const bool IsNearlyEqual(const double x, const double b);
	//Radians to Degrees conversion.
	static const double RadiansToDegrees(const double radians);
	//Degrees to Radians conversion.
	static const double DegreesToRadians(const double radians);
	//Gets a Vector2 direction from a given angle (degrees).
	static const Vector2 GetDirectionFromAngle(const float angle);
	//Gets an angle (degrees) in degs from a given Vector2 direction.
	static const double GetAngleFromDirection(const Vector2& direction);
};


