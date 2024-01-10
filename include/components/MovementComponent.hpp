#pragma once

#include "utilities/Math.hpp"
#include "components/Component.hpp"

class MovementComponent : public Component {

public:

	MovementComponent(class GameObject* parent, const char* name = "NA_MovementComponent");
	~MovementComponent() override;

	virtual void Update(const float deltaTime) override;

	const float GetSpeed() const { return m_speed; };
	const float GetMaxSpeed() const { return m_max_speed; };
	const Vector2& GetVelocity() const { return m_velocity; };

	void SetSpeed(const float speed);
	void SetMaxSpeed(const float maxSpeed) { m_max_speed = maxSpeed; };
	void SetVelocity(const Vector2& newVelocity) { m_velocity = newVelocity; };

	void AddPositionDelta(const Vector2& deltaPosition);
	void SetRotationFollowsVelocity(const bool newFollowVelocity);
	void SetClampToScreen(const bool clampToScreen) { m_clampToScreen = clampToScreen; };


private:

	//Unit vector, direction of movement.
	Vector2 m_velocity;
	float m_speed = 0.f;
	float m_max_speed = 500.f;
	bool m_rotationFollowsVelocity = true;
	bool m_clampToScreen = true;

};
