#include "entities/Meteor.hpp"
#include "components/MovementComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "utilities/ResourceManager.hpp"

Meteor::Meteor(const Transform& transform, const char* name)
	:GameObject(transform, ResourceManager::meteorTexture, name)
{
	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetMaxSpeed(350.f);

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(false);
	m_collider = m_collisionComponent->AddCollider(ResourceManager::meteorTexture->GetDimensions() * 0.7f, Vector2(10, 10), true, "Meteor Collision");

}

Meteor::~Meteor()
{
}

void Meteor::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

	m_transform.SetRotation(m_transform.GetRotation() + 1.f);
}
