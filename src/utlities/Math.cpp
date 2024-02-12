#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>
#include <random>

#include "utilities/Math.hpp"


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

const float Vector2::Lenght() const
{
	const float sqr = static_cast<float>(std::sqrt(std::pow(x, 2) + std::pow(y, 2)));
	return sqr;
}

const float Vector2::Dot(const Vector2& other) const {
	return this->x * other.x + this->y * other.y;
}

const float Vector2::AngleTo(const Vector2& other) const {
	Vector2 corrected = Vector2(this->x, -this->y);
	return Math::RadiansToDegrees(std::acos(corrected.Dot(other) / (corrected.Lenght() * other.Lenght())));
}

const Vector2 Vector2::Normalized() const
{
	const float lenght = Lenght() > 0.f ? Lenght() : 1.f;
	return Vector2(*this / lenght);
}

const Vector2 Vector2::RotatedBy(const float angle) const
{

	if (Math::IsNearlyEqual(angle, 0.f))
		return *this;
	Vector2 rotatedAtOrigin (
		this->x * sin(angle) - this->y * cos(angle),
		this->x * cos(angle) + this->y * sin(angle)
	);
	return rotatedAtOrigin;
}

const Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

const Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

const Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

const bool Vector2::operator==(const Vector2& other) const
{
	return this->x == other.x && this->y == other.y;
}

const Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(x / scalar, y / scalar);
}

void Vector2::operator+=(const Vector2& other) {
	*this = *this + other;
}

void Vector2::operator-=(const Vector2& other)
{
	*this = *this - other;
}

void Vector2::operator*=(float scalar)
{
	*this = *this * scalar;
}

void Vector2::Print() const {
	std::cout << "(" << x << ", " << y << ")" << std::endl;
}

/* MATH */

const Vector2 Math::GetDirectionFromAngle(const float angle)
{
	float safeAngle = angle;
	if (angle < 0.f) {
		safeAngle = 360.f + angle;
	}
	
	const float y = -std::sin(DegreesToRadians(safeAngle));
	const float x = std::cos(DegreesToRadians(safeAngle));

	return Vector2(x, y);
}

const float Math::GetAngleFromDirection(const Vector2& direction)
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

const Vector2 Math::Lerp(const Vector2& a, const Vector2& target, const float factor)
{
	const Vector2 difference = target - a;
	return difference * factor + a;
}

const int Math::RandomRange(const int from, const int to)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> randDist(from, to);

	return randDist(gen);
}

const bool Math::IsNearlyEqual(const float x, const float y)
{
	const float epsilon = 1e-5f;
	return std::abs(x - y) <= epsilon;
}

const float Math::RadiansToDegrees(const float radians) {
	return radians * (180.f / static_cast<float>(M_PI));
}

const float Math::DegreesToRadians(const float degrees) {
	return degrees * (static_cast<float>(M_PI) / 180.f);
}

