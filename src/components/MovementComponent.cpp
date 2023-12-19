
#include "MovementComponent.hpp"
#include "GameObject.hpp"

MovementComponent::MovementComponent(GameObject* parent, const char* name)
	:Component(parent, name),
	m_velocity(Vector2::ZERO),
	m_speed(0.f),
	m_rotationFollowsVelocity(false)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Update(const float deltaTime)
{
	if (m_rotationFollowsVelocity and !Math::IsNearlyEqual(m_velocity.Lenght(), 0.0)) {
		const float angle = Math::GetAngleFromDirection(m_velocity);
		m_parent->m_transform.SetRotation(angle);
	}
	AddPositionDelta(m_velocity * m_speed);

}

void MovementComponent::AddPositionDelta(const Vector2& deltaPosition)
{
	Vector2 newPosition = m_parent->m_transform.GetPosition() + deltaPosition;
	m_parent->m_transform.SetPosition(newPosition);
}

void MovementComponent::SetRotationFollowsVelocity(const bool newFollowVelocity)
{
	m_rotationFollowsVelocity = newFollowVelocity;
}

void MovementComponent::SetSpeed(const float newSpeed)
{
	m_speed = newSpeed;
}
