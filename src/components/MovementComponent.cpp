
#include "MovementComponent.hpp"
#include "GameObject.hpp"

MovementComponent::MovementComponent(GameObject* parent, const char* name)
	:Component(parent, name)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Update(const float deltaTime)
{
	AddPositionDelta(m_parent->GetVelocity());
}

void MovementComponent::AddPositionDelta(const Vector2& deltaPosition)
{
	m_parent->SetPoisiton(m_parent->GetPosition() + deltaPosition);
}
