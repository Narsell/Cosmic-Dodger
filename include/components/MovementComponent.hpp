#pragma once

#include "Math.hpp"
#include "Component.hpp"

class MovementComponent : public Component {

public:

	MovementComponent(class GameObject* parent, const char* name = "NA_MovementComponent");
	~MovementComponent() override;

	virtual void Update(const float deltaTime) override;

	void AddPositionDelta(const Vector2& deltaPosition);

	void SetFollowRotation(const bool newFollowRotation);
	void SetSpeed(const float newSpeed);

private:

	Vector2 velocity;
	bool m_followRotation = true;
	float m_speed = 0;
};
