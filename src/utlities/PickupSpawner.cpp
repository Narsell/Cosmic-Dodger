#include "utilities/PickupSpawner.hpp"
#include "entities/Pickup.hpp"
#include "entities/Player.hpp"
#include "GameManager.hpp"
#include "Window.hpp"

std::list<Pickup*> PickupSpawner::m_activePickups;


PickupSpawner::PickupSpawner(const char* name)
	:BaseEntity("", name)
{
}

PickupSpawner::~PickupSpawner()
{
}

void PickupSpawner::Update(const float deltaTime)
{
	m_timeSinceLastSpawn += deltaTime;

	if (m_timeSinceLastSpawn > m_currentSpawnRate && m_activePickups.size() < m_maxActivePicups) {
		SpawnPickup();
		m_timeSinceLastSpawn = 0.f;
	}
}

void PickupSpawner::SpawnPickup()
{
	Vector2 spawnPosition = GetRandomSpawnPoint();
	m_activePickups.emplace_back(
		GameManager::SpawnEntity(new Pickup(spawnPosition))
	);
}

Vector2 PickupSpawner::GetRandomSpawnPoint()
{
	const int areaPadding = 100;
	const int maxWidth = Window::s_width - areaPadding;
	const int maxHeight = Window::s_height - areaPadding;

	Vector2 newSpawnpoint = Vector2::ZERO;
	float distanceToLastSpawn = 0;
	float distanceToPlayer = 0;
	int iterations = 0;

	do {
		if (iterations > m_maxAttempts - 1)
			break;

		newSpawnpoint = Vector2(
			static_cast<float>(Math::RandomRange(areaPadding, maxWidth)),
			static_cast<float>(Math::RandomRange(areaPadding, maxHeight))
		);

		distanceToLastSpawn = m_activePickups.size() > 0
			? (m_activePickups.back()->m_transform.GetPosition() - newSpawnpoint).Lenght()
			: m_minDistanceToNextPickup;
		distanceToPlayer = (GameManager::GetPlayer()->m_transform.GetPosition() - newSpawnpoint).Lenght();
		++iterations;

	} while (
		distanceToLastSpawn < m_minDistanceToNextPickup || 
		distanceToPlayer < m_minDistanceToPlayer || 
		newSpawnpoint == Vector2::ZERO
		);

	return newSpawnpoint;

}

void PickupSpawner::DeletePickup(Pickup* pickup)
{
	m_activePickups.remove(pickup);
	GameManager::DestroyEntity(pickup);
}

void PickupSpawner::Reset()
{
	m_timeSinceLastSpawn = 0.f;
	for (Pickup*& pickup : m_activePickups)
	{
		GameManager::DestroyEntity(pickup);
	}
	m_activePickups.clear();
}

