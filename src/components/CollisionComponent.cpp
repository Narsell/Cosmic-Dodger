#include <SDL.h>
#include <assert.h>

#include "CollisionComponent.hpp"
#include "Collider2D.hpp"
#include "GameObject.hpp"


CollisionComponent::CollisionComponent(GameObject* parent)
	:Component(parent)
{
}

void CollisionComponent::AddCollider(const Vector2& dimensions, const Vector2& relativePos, const bool renderBounds)
{
	m_colliders.emplace_back(
		new Collider2D(dimensions, relativePos, renderBounds)
	);
}

void CollisionComponent::Update(const float deltaTime)
{
	assert(m_parent);
	m_position.x = m_parent->GetPosition().x;
	m_position.y = m_parent->GetPosition().y;
	for (Collider2D* collider : m_colliders) {
		collider->Update(deltaTime);
	}
}















//CollisionComponent::CollisionComponent(const Vector2& dimensions, const Vector2& relativePos, const bool renderBounds)
//	:
//	m_position(relativePos),
//	m_colliderRectangle({0, 0, dimensions.x, dimensions.y}),
//	bRenderBounds(renderBounds)
//{
//}
//
//CollisionComponent::CollisionComponent()
//	:
//	m_position(Vector2::ZERO),
//	m_colliderRectangle(SDL_Rect(0, 0, 0, 0)), 
//	bRenderBounds(false)
//{
//}
//
//CollisionComponent::~CollisionComponent()
//{
//}
//
//void CollisionComponent::Update(const float deltaTime, const Entity* parent)
//{
//	m_colliderRectangle.x = parent->GetPosition().x + m_position.x;
//	m_colliderRectangle.y = parent->GetPosition().y + m_position.y;
//}
//
//SDL_bool CollisionComponent::IsColliding(const CollisionComponent* other) const
//{
//	assert(other);
//	return SDL_HasIntersection(&m_colliderRectangle, &other->m_colliderRectangle);
//}
//
//SDL_bool CollisionComponent::IsColliding(const std::vector<CollisionComponent*> others) const
//{
//	for (CollisionComponent* other : others) {
//		if (IsColliding(other))
//			return SDL_TRUE;
//	}
//	return SDL_FALSE;
//}