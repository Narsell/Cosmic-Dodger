#include "utilities/PickupSpawner.hpp"
#include "entities/EnergyPickup.hpp"
#include "GameManager.hpp"
#include "Window.hpp"

std::list<EnergyPickup*> PickupSpawner::m_activePickups;


PickupSpawner::PickupSpawner()
{
}

PickupSpawner::~PickupSpawner()
{
}

void PickupSpawner::Update(const float deltaTime)
{
	m_timeSinceLastSpawn += deltaTime;

	if (m_timeSinceLastSpawn > m_spawnRate && m_activePickups.size() < m_maxActivePicups) {
		SpawnPickup();
		m_timeSinceLastSpawn = 0.f;
	}
}

void PickupSpawner::SpawnPickup()
{
	Vector2 spawnPosition = GetRandomSpawnPoint();
	m_activePickups.emplace_back(
		GameManager::SpawnEntity(new EnergyPickup(spawnPosition))
	);
}

Vector2 PickupSpawner::GetRandomSpawnPoint()
{
	const int areaPadding = 100;
	const int maxWidth = Window::s_width - areaPadding;
	const int maxHeight = Window::s_height - areaPadding;

	Vector2 newSpawnpoint = Vector2(
		static_cast<float>(Math::RandomRange(areaPadding, maxWidth)),
		static_cast<float>(Math::RandomRange(areaPadding, maxHeight))
	);

	if (m_activePickups.size() > 1) {
		
		float distanceToLastSpawn = (m_activePickups.back()->m_transform.GetPosition() - newSpawnpoint).Lenght();
		while (distanceToLastSpawn < m_minDistanceToNextPickup)
		{
			newSpawnpoint = Vector2(
				static_cast<float>(Math::RandomRange(areaPadding, maxWidth)),
				static_cast<float>(Math::RandomRange(areaPadding, maxHeight))
			);
			distanceToLastSpawn = (m_activePickups.back()->m_transform.GetPosition() - newSpawnpoint).Lenght();

		}

	}

	return newSpawnpoint;

}

void PickupSpawner::DeletePickup(EnergyPickup* pickup)
{
	m_activePickups.remove(pickup);
	GameManager::DestroyEntity(pickup);
}

