#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>

#include "Math.hpp"


/* VECTOR2 */

Vector2 Vector2::ZERO = Vector2(0.f, 0.f);
Vector2 Vector2::RIGHT = Vector2(1.f, 0.f);
Vector2 Vector2::LEFT = Vector2(-1.f, 0.f);
Vector2 Vector2::UP = Vector2(0.f, -1.f);
Vector2 Vector2::DOWN = Vector2(0.f, 1.f);

Vector2::Vector2()
	:x(0.f), y(0.f)
{}

Vector2::Vector2(float xy)
	:x(xy), y(xy)
{}

Vector2::Vector2(float p_x, float p_y)
	:x(p_x), y(p_y)
{}

const double Vector2::Lenght() const
{
	return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

const float Vector2::Dot(const Vector2& other) const {
	return this->x * other.x + this->y * other.y;
}

const float Vector2::AngleTo(const Vector2& other) const {
	Vector2 corrected = Vector2(this->x, -this->y);
	return Math::RadiansToDegrees(std::acos(corrected.Dot(other) / (corrected.Lenght() * other.Lenght())));
}

const Vector2& Vector2::Normalized() const
{
	const float lenght = Lenght() > 0.0 ? Lenght() : 1.f;
	return *new Vector2(*this / lenght);
}

const Vector2& Vector2::operator+(const Vector2& other) const
{
	return *new Vector2(x + other.x, y + other.y);
}

void Vector2::operator+=(const Vector2& other) {
	*this = *this + other;
}

const Vector2& Vector2::operator-(const Vector2& other) const
{
	return *new Vector2(x - other.x, y - other.y);
}

void Vector2::operator-=(const Vector2& other)
{
	*this = *this - other;
}

const Vector2& Vector2::operator*(float scalar) const
{
	return *new Vector2(x * scalar, y * scalar);
}

void Vector2::operator*=(float scalar)
{
	*this = *this * scalar;
}

const Vector2& Vector2::operator/(float scalar) const
{
	return *new Vector2(x / scalar, y / scalar);
}

void Vector2::Print() const {
	std::cout << "(" << x << ", " << y << ")" << std::endl;
}

/* MATH */

const Vector2& Math::GetDirectionFromAngle(const float angle)
{
	float safeAngle = angle;
	if (angle < 0) {
		safeAngle = 360 + angle;
	}
	float x = std::cos(DegreesToRadians(safeAngle));
	float y = std::sin(DegreesToRadians(safeAngle));
	return *new Vector2(x, y);
}

const double Math::GetAngleFromDirection(const Vector2& direction)
{
	float angle = 0.0f;
	const Vector2 normalDirection = direction.Normalized();
	if (normalDirection.x > 0.0 && normalDirection.y > 0.0 || normalDirection.x > 0.0 && normalDirection.y < 0.0) {
		angle = std::asin(-normalDirection.y);
	}
	else if (normalDirection.x < 0.0 && normalDirection.y > 0.0) {
		angle = -std::acos(normalDirection.x);
	}
	else if (normalDirection.x < 0.0 && normalDirection.y < 0.0) {
		angle = std::acos(normalDirection.x);
	}

	return RadiansToDegrees(angle);
}

const bool Math::IsNearlyEqual(const double x, const double y)
{
	const double epsilon = 1e-5;
	return std::abs(x - y) <= epsilon;
}

const double Math::RadiansToDegrees(const double radians) {
	return radians * (180.0 / M_PI);
}

const double Math::DegreesToRadians(const double degrees) {
	return degrees * (M_PI / 180.0);
}


