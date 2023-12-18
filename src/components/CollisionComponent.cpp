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

void CollisionComponent::AddCollider(const Vector2& dimensions, const Vector2& relativePos, const bool visible, const char* name)
{
	m_colliders.emplace_back(
		new Collider2D(dimensions, this, relativePos, visible, name)
	);
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

	m_position.x = m_parent->m_transform.GetPosition().x;
	m_position.y = m_parent->m_transform.GetPosition().y;

	for (Collider2D* collider : m_colliders) {
		collider->Update(deltaTime);
		for (CollisionComponent* collisionCandidate : m_collisionCandidates) {
			if (collider->IsColliding(collisionCandidate->GetAllColliders(), lastHitInformation)) {
				if(OnCollisionDelegate)
					OnCollisionDelegate(lastHitInformation);
			}
		}
	}
}

void CollisionComponent::SetCollisionDelegate(std::function<void(HitInformation&)> delegate)
{
	OnCollisionDelegate = delegate;
}

void CollisionComponent::ListenForCollisions(GameObject* collisionCandidate)
{
	assert(collisionCandidate);
	CollisionComponent* collisionComponent = collisionCandidate->GetComponentOfType<CollisionComponent>();
	if (collisionComponent) {
		m_collisionCandidates.emplace_back(collisionComponent);
	}
	else {
		std::cout << "Unable to get collision component from object " << collisionCandidate->GetDisplayName() << "\n";
	}
}
