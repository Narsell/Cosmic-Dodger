#pragma once

#include "Math.hpp"
#include "Component.hpp"

class MovementComponent : public Component {

public:

	MovementComponent(class GameObject* parent, const char* name = "NA_MovementComponent");
	~MovementComponent() override;

	virtual void Update(const float deltaTime) override;
	void AddPositionDelta(const Vector2& deltaPosition);


	const Vector2& GetVelocity() const { return m_velocity; };

	void SetVelocity(const Vector2& newVelocity) { m_velocity = newVelocity; };
	void SetRotationFollowsVelocity(const bool newFollowVelocity);
	void SetSpeed(const float newSpeed);

private:

	//Unit vector, direction of movement.
	Vector2 m_velocity;
	float m_speed = 0.f;
	bool m_rotationFollowsVelocity = true;

};
