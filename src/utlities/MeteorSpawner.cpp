#include "utilities/MeteorSpawner.hpp"
#include "entities/Meteor.hpp"
#include "entities/Player.hpp"
#include "GameManager.hpp"
#include "Window.hpp"


std::list<Meteor*> MeteorSpawner::m_activeMeteors;

MeteorSpawner::MeteorSpawner()
	:m_player(GameManager::GetPlayer())
{
	SpawnMeteor();
}

MeteorSpawner::~MeteorSpawner()
{
}

void MeteorSpawner::Reset()
{
	m_timeSinceLastSpawn = 0.f;
	for (Meteor* meteor : m_activeMeteors) 
	{
		GameManager::DestroyEntity(meteor);
	}
	m_activeMeteors.clear();
}

void MeteorSpawner::Update(const float deltaTime) {

	m_timeSinceLastSpawn += deltaTime;

	if (m_timeSinceLastSpawn > m_spawnRate) {
		SpawnMeteor();
		m_timeSinceLastSpawn = 0.f;
	}
}

const std::list<Meteor*>& MeteorSpawner::GetActiveMeteors()
{
	return m_activeMeteors;
}

void MeteorSpawner::DeleteMeteor(Meteor* meteor)
{
	m_activeMeteors.remove(meteor);
	GameManager::DestroyEntity(meteor);
}

void MeteorSpawner::SpawnMeteor()
{
	Vector2 spawnPosition = GetRandomSpawnPoint();
	Vector2 playerPosition = m_player->m_transform.GetPosition();
	Vector2 velocity = (playerPosition - spawnPosition).Normalized();
	m_activeMeteors.emplace_back(
		GameManager::SpawnEntity(new Meteor(spawnPosition, velocity, this))
	);
}

const Vector2 MeteorSpawner::GetRandomSpawnPoint() const
{
	/* 
		0: Random position from the upper side of the window.
		1: Random position from the right side of the window.
		2: Random position from the bottom side of the window.
		3: Random position from the left side of the window.
	*/


	const int side = Math::RandomRange(0, 3);
	const float windowOffset = 100.f;
	const Vector2 randomPoint(
		static_cast<float>(Math::RandomRange(0, Window::s_width)),
		static_cast<float>(Math::RandomRange(0, Window::s_height))
	);
	switch (side)
	{
	case 0:
		return Vector2(randomPoint.x, -windowOffset);
		break;
	case 1:
		return Vector2(Window::s_width + windowOffset, randomPoint.y);
		break;
	case 2:
		return Vector2(randomPoint.x, Window::s_height + windowOffset);
		break;
	case 3:
		return Vector2(-windowOffset, randomPoint.y);
		break;
	default:
		return Vector2::ZERO;
		break;
	}
}
