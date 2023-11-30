#include <SDL.h>
#include <assert.h>

#include "Collider2D.hpp"
#include "GameObject.hpp"


Collider2D::Collider2D(const Vector2& dimensions, const Vector2& relativePos, const bool renderBounds)
	:
	m_position(relativePos),
	m_colliderRectangle({ 0, 0, dimensions.x, dimensions.y }),
	bRenderBounds(renderBounds)
{
}

Collider2D::Collider2D()
	:
	m_position(Vector2::ZERO),
	m_colliderRectangle(SDL_Rect(0, 0, 0, 0)),
	bRenderBounds(false)
{
}

Collider2D::~Collider2D()
{
}

void Collider2D::Update(const float deltaTime)
{
	//m_colliderRectangle.x = parent->GetPosition().x + m_position.x;
	//m_colliderRectangle.y = parent->GetPosition().y + m_position.y;
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