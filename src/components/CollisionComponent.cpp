#include <SDL.h>
#include <assert.h>
#include <iostream>

#include "CollisionComponent.hpp"
#include "Collider2D.hpp"


CollisionComponent::CollisionComponent(GameObject* parent, const char* name)
	:Component(parent, name)
{}

CollisionComponent::~CollisionComponent()
{
	//std::cout << GetDisplayName() << " destroyed on CollisionComponent destructor!\n";

	for (Collider2D* collider : m_colliders) {
		delete collider;
	}
}

Collider2D* CollisionComponent::AddCollider(const Vector2& dimensions, const Vector2& relativePos, const bool visible, const char* name)
{
	m_colliders.emplace_back(
		new Collider2D(dimensions, this, relativePos, visible, name)
	);
	return m_colliders.back();
}

void CollisionComponent::Render(SDL_Renderer* renderer)
{
	Component::Render(renderer);

	for (Collider2D* collider : m_colliders) {
		if (collider->GetCanRender()) {
			collider->Render(renderer);
		}
	}
}

void CollisionComponent::Update(const float deltaTime)
{
	Component::Update(deltaTime);

	m_position = m_parent->m_transform.GetPosition();

	for (Collider2D* collider : m_colliders) {
		if (collider->GetCanUpdate()) {
			collider->Update(deltaTime);
		}
	}
}

void CollisionComponent::SetCanUpdate(const bool canUpdate)
{
	BaseEntity::SetCanUpdate(canUpdate);

	for (Collider2D* collider : m_colliders) {
		collider->SetCanUpdate(canUpdate);
	}
}

