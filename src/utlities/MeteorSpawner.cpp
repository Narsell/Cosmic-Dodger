#include "utilities/MeteorSpawner.hpp"
#include "entities/Meteor.hpp"
#include "GameManager.hpp"
#include "entities/Player.hpp"
#include "Window.hpp"


std::list<Meteor*> MeteorSpawner::m_activeMeteors;

MeteorSpawner::MeteorSpawner()
	:m_player(GameManager::GetPlayer())
{
	SpawnMeteor();
}

MeteorSpawner::~MeteorSpawner()
{
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
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> sideDist(0, 3);
	std::uniform_int_distribution<> xDist(0, Window::s_width);
	std::uniform_int_distribution<> yDist(0, Window::s_height);

	const int side = sideDist(gen);
	const float windowOffset = 100.f;
	const Vector2 randomPoints(static_cast<float>(xDist(gen)), static_cast<float>(yDist(gen)));
	switch (side)
	{
	case 0:
		return Vector2(randomPoints.x, -windowOffset);
		break;
	case 1:
		return Vector2(Window::s_width + windowOffset, randomPoints.y);
		break;
	case 2:
		return Vector2(randomPoints.x, Window::s_height + windowOffset);
		break;
	case 3:
		return Vector2(-windowOffset, randomPoints.y);
		break;
	default:
		return Vector2::ZERO;
		break;
	}
}
