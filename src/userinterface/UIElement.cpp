#include "userinterface/UIElement.hpp"

UIElement::UIElement(const HUD* parentHud, const Transform& transform, const char* name)
	:BaseEntity("", name, true, false),
	m_parentHud(parentHud),
	m_transform(transform)
{
}
