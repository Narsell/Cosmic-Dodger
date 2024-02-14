#pragma once
#include <list>
#include <random>

#include "utilities/Math.hpp"
#include "entities/BaseEntity.hpp"

class Meteor;
class Player;

class MeteorSpawner: public BaseEntity {

public:

	MeteorSpawner();
	~MeteorSpawner() override;

	//Resets spawner timer and deletes all active meteors
	void Reset();

	virtual void Update(const float deltaTime) override;

	void IncreaseDifficulty();

	static const std::list<Meteor*>& GetActiveMeteors();
	static void DeleteMeteor(Meteor* meteor);
	
private:

	void SpawnMeteor();
	const Vector2 GetRandomSpawnPoint() const;
	void SetSpawnRate(const float spawnRate);
	void SetMeteorSpeed(const float speed);

private:

	const float m_spawnDecrementRate = 0.1f;
	const float m_minSpawnRate = 0.5f;
	const float m_maxSpawnRate = 1.5f;
	float m_currentSpawnRate = m_maxSpawnRate;
	float m_timeSinceLastSpawn = 0.f;

	const float m_minMeteorSpeed = 250.f;
	float m_currentMeteorSpeed = m_minMeteorSpeed;
	float m_speedIncrementRate = 20.f;

	const Player* m_player = nullptr;
	static std::list<Meteor*> m_activeMeteors;

};
