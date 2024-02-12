#include <functional>

#include "entities/Pickup.hpp"
#include "entities/Player.hpp"
#include "components/CollisionComponent.hpp"
#include "utilities/ResourceManager.hpp"
#include "utilities/PickupSpawner.hpp"
#include "utilities/GameState.hpp"
#include "GameManager.hpp"


Pickup::Pickup(const Transform& transform, const char* name)
	:GameObject(transform, ResourceManager::pickupTexture),
	m_pickUpSound(ResourceManager::pickUpSound, 0.5f),
	m_startPosition(transform.GetPosition()),
	m_velocity(0, -60)
{
	m_transform.SetRotation(90.f);
	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(false);
	m_collider = m_collisionComponent->AddCollider(ResourceManager::meteorTexture->GetDimensions() * 0.7f, Vector2::ZERO, true, "Fuel Grab Collision");
	std::function<void(HitInfo&)> OnCollisionDelegate = std::bind(&Pickup::OnCollision, this, std::placeholders::_1);
	m_collider->SetCollisionDelegate(OnCollisionDelegate);
	m_collider->ListenForCollisions(GameManager::GetPlayer());
}

Pickup::~Pickup()
{
}

void Pickup::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);
	BounceAnimation(deltaTime);
}

void Pickup::OnCollision(HitInfo& hitInfo)
{
	m_pickUpSound.Play();
	PickupSpawner::DeletePickup(this);
	GameState::GetGameState()->AddScore(1);
}

void Pickup::BounceAnimation(const float deltaTime)
{
	const Vector2 currentPosition = m_transform.GetPosition();
	const float distanceTraveled = (currentPosition - m_startPosition).Lenght();

	if (distanceTraveled > m_maxFloatingDistance) {
		m_startPosition = m_startPosition + m_velocity.Normalized() * m_maxFloatingDistance;
		m_velocity *= -1;
	}
	else {
		const Vector2 newPosition = currentPosition + m_velocity * deltaTime;
		m_transform.SetPosition(newPosition);
	}

}
