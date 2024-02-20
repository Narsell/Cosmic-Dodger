#pragma once
#include "components/Transform.hpp"
#include "entities/BaseEntity.hpp"

class HUD;

class UIElement : public BaseEntity {

public:

	UIElement(const HUD* parentHud, const Transform& transform = Transform(), const char* name = "NA_UIElement");

	Transform m_transform;

protected:

	const HUD* GetParentHud() const { return m_parentHud; };

private:

	const HUD* m_parentHud;
};
