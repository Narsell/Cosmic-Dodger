#include "components/Transform.hpp"

Transform::Transform(const Vector2& position, const float rotation, const float scale)
	:
	m_position(position),
	m_rotation(rotation),
	m_scale(scale)
{}

const Transform Transform::operator+(const Transform& other) const
{
	return Transform(
		Vector2(this->m_position + other.m_position),
		this->m_rotation + other.m_rotation,
		this->m_scale * other.m_scale
	);
}

void Transform::operator+=(const Transform& other)
{
	*this = *this + other;
}

void Transform::SetRotation(const float newRotation)
{
	float boundAngle = newRotation;
	if (newRotation > 360.f) {
		boundAngle = newRotation - 360.f;
	}
	m_rotation = boundAngle;
}
