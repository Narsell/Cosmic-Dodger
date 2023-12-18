#include <SDL.h>
#include <assert.h>
#include <cmath>

#include "Collider2D.hpp"
#include "GameObject.hpp"
#include "CollisionComponent.hpp"


Collider2D::Collider2D(const Vector2& dimensions, CollisionComponent* parentComp, const Vector2& relativePos, const bool visible, const char* name)
	:
	BaseEntity("", name, visible, true),
	m_position(relativePos),
	m_colliderRectangle({ 0, 0, (int)ceil(dimensions.x), (int)ceil(dimensions.y) }),
	m_parentComponent(parentComp)
{
}

Collider2D::~Collider2D()
{
	//std::cout << GetDisplayName() << " destroyed on Collider destructor!\n";

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

bool Collider2D::IsColliding(Collider2D* other, HitInformation& OutHitInformation) const
{
	assert(other);

	if (SDL_HasIntersection(&m_colliderRectangle, &other->m_colliderRectangle)) {

		CollisionComponent* parentCollisionComp = other->m_parentComponent;
		assert(parentCollisionComp);

		OutHitInformation.hasHit = true;
		OutHitInformation.hitLocation = m_parentComponent->GetPosition();
		OutHitInformation.hitCollider = other;
		OutHitInformation.hitGameObject = parentCollisionComp->GetParent();

		return true;
	}
	return false;
}

bool Collider2D::IsColliding(const std::vector<Collider2D*> others, HitInformation& OutHitInformation) const
{
	for (Collider2D* other : others) {
		if (IsColliding(other, OutHitInformation)) {
			return true;
		}
	}
	return false;
}