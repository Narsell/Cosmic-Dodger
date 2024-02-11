#include "components/MovementComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "entities/WindowBounds.hpp"
#include "entities/Meteor.hpp"
#include "entities/Projectile.hpp"
#include "utilities/ResourceManager.hpp"
#include "utilities/MeteorSpawner.hpp"
#include "utilities/GameState.hpp"
#include "GameManager.hpp"
#include "Window.hpp"

Projectile::Projectile(const Transform& transform, const char* name)
	:
	GameObject(transform, ResourceManager::projectileTexture, name)
{
	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(false);
	m_collider = m_collisionComponent->AddCollider(Vector2(18, 18), Vector2(0, -25), true, "Basic Collision");
	std::function<void(HitInfo&)> OnCollisionDelegate = std::bind(&Projectile::OnCollision, this, std::placeholders::_1);
	m_collider->SetCollisionDelegate(OnCollisionDelegate);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetMaxSpeed(2000.f);
	m_movementComponent->SetSpeed(1500.f);
	m_movementComponent->SetRotationFollowsVelocity(true);

	m_startPosition = m_transform.GetPosition();
}

Projectile::~Projectile()
{
}

void Projectile::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Projectile::OnCollision(HitInfo& hitInformation)
{

	if (hitInformation.hitGameObject->GetDisplayName() == "NA_Meteor")
	{
		GameManager::DestroyEntity(this);
		GameState::GetGameState()->AddScore(1);
		// TODO: Add a more robust collision channel system to avoid this.
		// Each object should get their own collision callback to handle their specific functionality.
		// Instead, we're calling the meteor's spawner and deleting it from here, not ideal but that's a problem
		// for future me.
		Meteor* meteor = dynamic_cast<Meteor*>(hitInformation.hitGameObject);
		if (meteor) {
			MeteorSpawner::DeleteMeteor(meteor);
		}
	}
	else if (hitInformation.hitGameObject->GetDisplayName() == "Window Bounds")
	{
		++m_bouncesCounter;
		if (m_bouncesCounter >= m_maxBounces) {
			GameManager::DestroyEntity(this);
			return;
		}

		const Vector2 currentVelocity = m_movementComponent->GetVelocity();

		if (hitInformation.hitCollider->GetDisplayName() == "UP" || hitInformation.hitCollider->GetDisplayName() == "DOWN") 
		{
			const Vector2 newVelocity = Vector2(currentVelocity.x, -currentVelocity.y);
			m_movementComponent->SetVelocity(newVelocity);
		}
		else if (hitInformation.hitCollider->GetDisplayName() == "RIGHT" || hitInformation.hitCollider->GetDisplayName() == "LEFT") 
		{
			const Vector2 newVelocity = Vector2(-currentVelocity.x, currentVelocity.y);
			m_movementComponent->SetVelocity(newVelocity);
		}
	}
}

void Projectile::SetWindowCollisions(WindowBounds* windowBounds)
{
	m_collider->ListenForCollisions(windowBounds->GetCollisionComponent()->GetAllColliders());
}
