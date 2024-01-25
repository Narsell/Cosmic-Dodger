#include "entities/Meteor.hpp"
#include "components/MovementComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "utilities/ResourceManager.hpp"
#include "utilities/MeteorSpawner.hpp"

Meteor::Meteor(const Transform& transform, const Vector2& initialVelocity, MeteorSpawner* spawner, const char* name)
	:GameObject(transform, ResourceManager::meteorTexture, name),
	m_spawner(spawner)
{
	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetVelocity(initialVelocity);
	m_movementComponent->SetSpeed(350.f);
	m_movementComponent->SetMaxSpeed(350.f);

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(false);
	m_collider = m_collisionComponent->AddCollider(ResourceManager::meteorTexture->GetDimensions() * 0.7f, Vector2::ZERO, true, "Meteor Collision");
	std::function<void(HitInfo&)> OnCollisionDelegate = std::bind(&Meteor::OnCollision, this, std::placeholders::_1);
	m_collider->SetCollisionDelegate(OnCollisionDelegate);
}

Meteor::~Meteor()
{
}

void Meteor::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

	m_aliveTime += deltaTime;

	m_distanceTraveled = m_movementComponent->GetSpeed() * m_aliveTime;

	if (m_distanceTraveled > m_maxDistanceTravel) {
		m_spawner->DeleteMeteor(this);
	}

	m_transform.SetRotation(m_transform.GetRotation() + 1.f);
}

void Meteor::OnCollision(HitInfo& hitInformation)
{
	m_spawner->DeleteMeteor(this);
}
