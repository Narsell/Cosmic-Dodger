#include "Math.hpp"


Vector2 Vector2::ZERO = Vector2(0.f, 0.f);

Vector2::Vector2()
	:x(0.0f), y(0.0f)
{}

Vector2::Vector2(float xy)
	:x(xy), y(xy)
{}

Vector2::Vector2(float p_x, float p_y)
	:x(p_x), y(p_y)
{}

void Vector2::operator+=(const Vector2 & deltaVector) {
	x += deltaVector.x;
	y += deltaVector.y;
}

void Vector2::Print() const {
	std::cout << x << ", " << y << std::endl;
}
