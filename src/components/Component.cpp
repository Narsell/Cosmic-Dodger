#include "Component.hpp"

Component::Component(GameObject* parent, const char* name, bool canRender, bool canUpdate)
	:
	BaseEntity("", name, canRender, canUpdate),
	m_parent(parent)
{
}
