#pragma once


#pragma once
#include <list>
#include <random>

#include "utilities/Math.hpp"
#include "entities/BaseEntity.hpp"

class Pickup;

class PickupSpawner : public BaseEntity {

public:

	PickupSpawner(const char* name);
	~PickupSpawner() override;

	virtual void Update(const float deltaTime) override;

	void SpawnPickup();
	static void DeletePickup(Pickup* pickup);
	void Reset();

private:

	Vector2 GetRandomSpawnPoint();

private:

	const float m_currentSpawnRate = 1.5f;
	float m_timeSinceLastSpawn = 0.f;

	const int m_maxActivePicups = 5;
	// Minimum distance to distance each pickup from the last spawned. Avoid values higher than 600.
	const float m_minDistanceToNextPickup = 400.f;
	// Minimum distance to player, to avoid spawning to close to the player. Avoid values higher than 300.
	const float m_minDistanceToPlayer = 200.f;
	//Max number of attempts to try and find a suitable spawn point given m_minDistanceToNextPickup and m_minDistanceToPlayer. (Infinite loop protection)
	const int m_maxAttempts = 20;

	static std::list<Pickup*> m_activePickups;


};
