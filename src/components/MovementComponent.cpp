
#include "MovementComponent.hpp"
#include "GameObject.hpp"

MovementComponent::MovementComponent(GameObject* parent, const char* name)
	:Component(parent, name),
	m_followRotation(true)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Update(const float deltaTime)
{
	if (m_followRotation) {
		const float rotation = m_parent->m_transform.GetRotation();
		velocity = Math::GetDirectionFromAngle(rotation);
	}
	else {
		velocity = Vector2::RIGHT;
	}
	AddPositionDelta(velocity * m_speed);
}

void MovementComponent::AddPositionDelta(const Vector2& deltaPosition)
{
	Vector2 newPosition = m_parent->m_transform.GetPosition() + deltaPosition;
	m_parent->m_transform.SetPosition(newPosition);
}

void MovementComponent::SetFollowRotation(const bool newFollowRotation)
{
	m_followRotation = newFollowRotation;
}

void MovementComponent::SetSpeed(const float newSpeed)
{
	m_speed = newSpeed;
}
