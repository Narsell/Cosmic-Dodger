#include "Component.hpp"

Component::Component(GameObject* parent)
	:
	BaseEntity("", "NA_Component"),
	m_parent(parent)
{
}
