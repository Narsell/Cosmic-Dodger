#include <assert.h>
#include <algorithm>

#include "components/ShootingComponent.hpp"
#include "components/MovementComponent.hpp"
#include "utilities/ResourceManager.hpp"
#include "components/Transform.hpp"
#include "entities/Projectile.hpp"
#include "entities/Player.hpp"
#include "entities/WindowBounds.hpp"
#include "GameManager.hpp"

ShootingComponent::ShootingComponent(GameObject* parent, const char* name)
	:Component(parent, name),
	m_shootingSound("assets/shoot2.wav")
{
	m_player = dynamic_cast<Player*>(m_parent);
	assert(m_player);
}

ShootingComponent::~ShootingComponent()
{
}

void ShootingComponent::Update(const float deltaTime)
{
	m_timeSinceLastShot += deltaTime;
	m_timeSinceLastReplenish += deltaTime;

	std::cout << "Current ammo: " << m_currentAmmo << "\n";

	if (m_timeSinceLastReplenish >= m_increaseAmmoTime) {
		m_currentAmmo = std::clamp(++m_currentAmmo, 0, m_maxAmmo);
		m_timeSinceLastReplenish = 0.f;
	}

}

void ShootingComponent::Shoot()
{
	if (m_timeSinceLastShot < m_shootingReloadTime || m_currentAmmo < 1 || m_player->GetIsMouseOnPlayer()) {
		return;
	}

	assert(ResourceManager::projectileTexture);

	const float rotation = m_parent->m_transform.GetRotation();
	const Vector2 lookAtDirection = Math::GetDirectionFromAngle(rotation);

	const Vector2 absoluteCenter = m_parent->m_transform.GetPosition() + m_parent->GetCenterPoint();
	Vector2 spawnPosition(absoluteCenter - ResourceManager::projectileTexture->GetDimensions() / 2.f + lookAtDirection * m_projetileSpawnDistance);
	Transform spawnTransform = Transform(spawnPosition, rotation);

	Projectile* projectile = new Projectile(spawnTransform, ResourceManager::projectileTexture, "Projectile");
	projectile->GetMovementComponent()->SetVelocity(lookAtDirection);
	projectile->SetWindowCollisions(m_player->GetWindowBounds());

	GameManager::SpawnGameObject(projectile);

	m_shootingSound.PlaySound();

	m_timeSinceLastShot = 0.f;
	m_currentAmmo = std::clamp(--m_currentAmmo, 0, m_maxAmmo);
}
