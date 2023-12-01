#pragma once
#include "BaseEntity.hpp"

class GameObject;

class Component : public BaseEntity {

public:

	virtual void Update(const float deltaTime) override {};
	virtual ~Component() {};

protected:

	Component(GameObject* parent);

	GameObject* m_parent = nullptr;
};
