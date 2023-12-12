#pragma once

#include "Math.hpp"
#include "Component.hpp"

class MovementComponent : public Component {

public:

	MovementComponent(class GameObject* parent, const char* name = "NA_MovementComponent");
	~MovementComponent() override;

	virtual void Update(const float deltaTime) override;

	void AddPositionDelta(const Vector2& deltaPosition);
};
