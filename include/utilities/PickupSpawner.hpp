#pragma once


#pragma once
#include <list>
#include <random>

#include "utilities/Math.hpp"
#include "entities/BaseEntity.hpp"

class EnergyPickup;

class PickupSpawner : public BaseEntity {

public:

	PickupSpawner();
	~PickupSpawner() override;

	virtual void Update(const float deltaTime) override;

	void SpawnPickup();
	static void DeletePickup(EnergyPickup* pickup);

private:

	Vector2 GetRandomSpawnPoint();

private:

	const float m_spawnRate = 1.5f;
	float m_timeSinceLastSpawn = 0.f;

	const int m_maxActivePicups = 10;
	// Minimum distance to distance each pickup from the last spawned. Be careful not to set to high or it could get stuck on a inf. while loop.
	const float m_minDistanceToNextPickup = 600.f;

	static std::list<EnergyPickup*> m_activePickups;


};
