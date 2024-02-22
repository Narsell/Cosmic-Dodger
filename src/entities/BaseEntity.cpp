#include <assert.h>
#include <iostream>

#include "entities/BaseEntity.hpp"

BaseEntity::BaseEntity(const char* entityId, const char* entityName, const bool canRender, const bool canUpdate)
	:
	m_id(entityId),
	m_displayName(entityName),
	m_canRender(canRender),
	m_canUpdate(canUpdate)

{
}

BaseEntity::~BaseEntity()
{
	//std::cout << GetDisplayName() << " destroyed on BaseEntity destructor!\n";
}

void BaseEntity::Render(SDL_Renderer* renderer)
{
	assert(renderer);
}

void BaseEntity::Update(const float deltaTime)
{
}

void BaseEntity::Disable()
{
	SetCanUpdate(false);
	SetCanRender(false);
}
