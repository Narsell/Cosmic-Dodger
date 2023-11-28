#include "Math.hpp"


Vector2 Vector2::ZERO = Vector2(0, 0);
Vector2 Vector2::RIGHT = Vector2(1, 0);
Vector2 Vector2::LEFT = Vector2(-1, 0);
Vector2 Vector2::UP = Vector2(0, -1);
Vector2 Vector2::DOWN = Vector2(0, 1);

Vector2::Vector2()
	:x(0), y(0)
{}

Vector2::Vector2(int xy)
	:x(xy), y(xy)
{}

Vector2::Vector2(int p_x, int p_y)
	:x(p_x), y(p_y)
{}

const Vector2& Vector2::operator+(const Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

void Vector2::operator+=(const Vector2& other) {
	*this = *this + other;
}

const Vector2& Vector2::operator-(const Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

void Vector2::operator-=(const Vector2& other)
{
	*this = *this - other;
}

const Vector2& Vector2::operator*(float scalar)
{
	return Vector2(x * scalar, y * scalar);
}

void Vector2::operator*=(float scalar)
{
	*this = *this * scalar;
}

void Vector2::Print() const {
	std::cout << "(" << x << ", " << y << ")" << std::endl;
}
