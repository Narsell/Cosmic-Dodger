#pragma once
#include <vector>

#include "components/Transform.hpp"
#include "entities/BaseEntity.hpp"

class HUD;

class UIElement : public BaseEntity {

public:

	~UIElement() {};

	void AddChild(UIElement* child);

	Transform m_transform;
	Transform m_relativeTransform;

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

protected:

	UIElement(const Transform& transform = Transform(), const char* name = "NA_UIElement");

private:

	const UIElement* m_parentElement = nullptr;
	std::vector<UIElement*> m_children;
};
