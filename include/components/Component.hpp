#pragma once
#include "BaseEntity.hpp"

class GameObject;
struct SDL_Renderer;

class Component : public BaseEntity {

public:

	virtual ~Component() {};

protected:

	Component(GameObject* parent);

	GameObject* m_parent = nullptr;
};
