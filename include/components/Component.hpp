#pragma once
#include "BaseEntity.hpp"

class GameObject;
struct SDL_Renderer;

class Component : public BaseEntity {

public:

	GameObject* GetParent() const { return m_parent; };

protected:

	Component(GameObject* parent, const char* name = "NA_Component", bool canRender = false, bool canUpdate = true);

	GameObject* m_parent = nullptr;
};
