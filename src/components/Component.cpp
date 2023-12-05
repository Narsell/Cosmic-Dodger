#include "Component.hpp"

Component::Component(GameObject* parent, const char* name)
	:
	BaseEntity("", name, false, true),
	m_parent(parent)
{
}
