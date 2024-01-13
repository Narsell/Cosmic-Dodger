#include "Transform.hpp"

void Transform::SetRotation(const float newRotation)
{
	float boundAngle = newRotation;
	if (newRotation > 360.f) {
		boundAngle = newRotation - 360.f;
	}
	m_rotation = boundAngle;
}
