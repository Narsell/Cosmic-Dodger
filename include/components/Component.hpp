#pragma once
#include "Math.hpp"
#include "BaseEntity.hpp"

class GameObject;

class Component : public BaseEntity {

public:

	virtual void Update(const float deltaTime) override {};
	virtual ~Component() {};

protected:
	//TODO: Remove default constructor?
	Component() {};
	Component(GameObject* parent);

	GameObject* m_parent = nullptr;
};
