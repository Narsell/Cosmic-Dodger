#include "Component.hpp"

Component::Component(GameObject* parent)
	:
	BaseEntity("", "NA_Component", false, true),
	m_parent(parent)
{
}
