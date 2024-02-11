#include "entities/Meteor.hpp"
#include "entities/Player.hpp"
#include "components/MovementComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "utilities/ResourceManager.hpp"
#include "utilities/MeteorSpawner.hpp"
#include "utilities/GameState.hpp"
#include "GameManager.hpp"

Meteor::Meteor(const Transform& transform, const Vector2& initialVelocity, MeteorSpawner* spawner, const char* name)
	:GameObject(transform, ResourceManager::meteorTexture, name),
	m_spawner(spawner)
{
	while (m_rotationRate == 0) {
		m_rotationRate = Math::RandomRange(-1, 1);
	}

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetVelocity(initialVelocity);
	m_movementComponent->SetSpeed(250.f);
	m_movementComponent->SetMaxSpeed(250.f);

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(false);
	m_collider = m_collisionComponent->AddCollider(ResourceManager::meteorTexture->GetDimensions() * 0.7f, Vector2::ZERO, true, "Meteor Collision");
	std::function<void(HitInfo&)> OnCollisionDelegate = std::bind(&Meteor::OnCollision, this, std::placeholders::_1);
	m_collider->SetCollisionDelegate(OnCollisionDelegate);
	m_collider->ListenForCollisions(GameManager::GetPlayer());
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

	m_transform.SetRotation(m_transform.GetRotation() + m_rotationRate);
}

void Meteor::OnCollision(HitInfo& hitInformation)
{
	hitInformation.Print();
	GameState::GetGameState()->PlayerHit();
	m_spawner->DeleteMeteor(this);
}
