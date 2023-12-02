#pragma once
#include "BaseEntity.hpp"

class GameObject;
struct SDL_Renderer;

class Component : public BaseEntity {

public:

	virtual void Render(SDL_Renderer* renderer) override = 0;
	virtual void Update(const float deltaTime) override = 0;
	virtual ~Component() {};

protected:

	Component(GameObject* parent);

	GameObject* m_parent = nullptr;
};
