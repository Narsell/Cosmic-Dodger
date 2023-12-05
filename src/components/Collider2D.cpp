#include <SDL.h>
#include <assert.h>

#include "Collider2D.hpp"
#include "GameObject.hpp"
#include "CollisionComponent.hpp"


Collider2D::Collider2D(const Vector2& dimensions, CollisionComponent* parentComp, const Vector2& relativePos, const bool visible)
	:
	BaseEntity("", "NA_Collider2D", visible, true),
	m_position(relativePos),
	m_colliderRectangle({ 0, 0, dimensions.x, dimensions.y }),
	m_parentComponent(parentComp)
{
}

Collider2D::~Collider2D()
{
}

void Collider2D::Render(SDL_Renderer* renderer)
{
	BaseEntity::Render(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &m_colliderRectangle);
}

void Collider2D::Update(const float deltaTime)
{
	BaseEntity::Update(deltaTime);

	m_colliderRectangle.x = m_parentComponent->GetPosition().x + m_position.x;
	m_colliderRectangle.y = m_parentComponent->GetPosition().y + m_position.y;
}

SDL_bool Collider2D::IsColliding(const Collider2D* other) const
{
	assert(other);
	return SDL_HasIntersection(&m_colliderRectangle, &other->m_colliderRectangle);
}

SDL_bool Collider2D::IsColliding(const std::vector<Collider2D*> others) const
{
	for (Collider2D* other : others) {
		if (IsColliding(other))
			return SDL_TRUE;
	}
	return SDL_FALSE;
}