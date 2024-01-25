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
	~MeteorSpawner();

	virtual void Update(const float deltaTime) override;

	static const std::list<Meteor*>& GetActiveMeteors();
	static void DeleteMeteor(Meteor* meteor);
	
private:

	void SpawnMeteor();
	const Vector2 GetRandomSpawnPoint() const;

private:

	const float m_spawnRate = 1.5f;
	float m_timeSinceLastSpawn = 0.f;

	const Player* m_player = nullptr;
	static std::list<Meteor*> m_activeMeteors;

};
