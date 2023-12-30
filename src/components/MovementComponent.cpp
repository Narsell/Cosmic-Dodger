
#include "MovementComponent.hpp"
#include "GameObject.hpp"

MovementComponent::MovementComponent(GameObject* parent, const char* name)
	:Component(parent, name),
	m_velocity(Vector2::ZERO),
	m_speed(0.f),
	m_rotationFollowsVelocity(false),
	m_clampToScreen(true)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::Update(const float deltaTime)
{
	if (m_rotationFollowsVelocity and !Math::IsNearlyEqual(m_velocity.Lenght(), 0.0)) {
		const double angle = Math::GetAngleFromDirection(m_velocity);
		m_parent->m_transform.SetRotation(angle);
	}
	AddPositionDelta(m_velocity * m_speed * deltaTime);

	/*
	TODO: Figure out a better way to clamp an object to the screen, refactor this into a method or something, maybe belongs on collisionComponent?
		  Also, need to detect object bounds based on a collision and not the object texture.
		  Possible could store a reference to the movement component and use the collision bounds (if there is any)
		  Problem for future self...
	*/

	//Commented out until TODO above is addressed as this is causing a bug with the projectile's collision.
	/*
	if (m_clampToScreen) {
		if (m_parent->m_transform.GetPosition().x <= 0) {
			m_parent->m_transform.SetPosition(Vector2(0.f, m_parent->m_transform.GetPosition().y));
		}
		else if (m_parent->m_transform.GetPosition().x + m_parent->GetCurrentFrame().w >= 1280.f) {
			m_parent->m_transform.SetPosition(Vector2(1280.f - m_parent->GetCurrentFrame().w, m_parent->m_transform.GetPosition().y));
		} 
		
		else if (m_parent->m_transform.GetPosition().y <= 0) {
			m_parent->m_transform.SetPosition(Vector2(m_parent->m_transform.GetPosition().x, 0.f));
		}
		else if (m_parent->m_transform.GetPosition().y + m_parent->GetCurrentFrame().h >= 720.f) {
			m_parent->m_transform.SetPosition(Vector2(m_parent->m_transform.GetPosition().x, 720.f - m_parent->GetCurrentFrame().h));
		}
	}
	*/

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
