#include "BaseEntity.hpp"

BaseEntity::BaseEntity()
	:
	m_id(""),
	m_displayName("NA_BaseEntity")
{
}

BaseEntity::BaseEntity(const char* entityId, const char* entityName)
	:
	m_id(entityId),
	m_displayName(entityName)
{
}
