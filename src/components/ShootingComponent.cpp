#include <assert.h>
#include <algorithm>

#include "components/ShootingComponent.hpp"
#include "components/MovementComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/Transform.hpp"
#include "utilities/ResourceManager.hpp"
#include "utilities/MeteorSpawner.hpp"
#include "entities/Projectile.hpp"
#include "entities/Player.hpp"
#include "entities/Meteor.hpp"
#include "entities/WindowBounds.hpp"
#include "userinterface/Hud.hpp"
#include "GameManager.hpp"

ShootingComponent::ShootingComponent(GameObject* parent, const char* name)
	:Component(parent, name),
	m_shootingSound(ResourceManager::shootingSound, 0.5f),
	m_player(dynamic_cast<Player*>(m_parent))
{
	assert(m_player);
	m_hud = m_player->GetHud();
	assert(m_hud);
	m_hud->UpdateAmmo(m_currentAmmo);
}

ShootingComponent::~ShootingComponent()
{
}

void ShootingComponent::Reset()
{
	m_currentAmmo = m_maxAmmo;
	m_timeSinceLastReplenish = 0.f;
	m_timeSinceLastShot = 0.f;
}

void ShootingComponent::Update(const float deltaTime)
{
	m_timeSinceLastShot += deltaTime;
	m_timeSinceLastReplenish += deltaTime;

	if (m_timeSinceLastReplenish >= m_increaseAmmoTime) {
		UpdateAmmo(m_currentAmmo + 1);
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

	Projectile* projectile = new Projectile(spawnTransform, "Projectile");
	projectile->GetMovementComponent()->SetVelocity(lookAtDirection);
	projectile->SetWindowCollisions(m_player->GetWindowBounds());

	// TODO: When a robust collision channel system is implemented, remove this.
	// This introduces a bug where a new meteor spawned just after the projectile will not register collisions with each other (Because they don't know about each other)
	// Since the projectile is fast enough this shouldn't be much of a problem for now, very difficult to reproduce.
	for (Meteor* meteor : MeteorSpawner::GetActiveMeteors()) {
		projectile->GetCollisionComponent()->GetColliderByIndex(0)->ListenForCollisions(meteor);
	}

	GameManager::SpawnEntity(projectile);

	m_shootingSound.Play();

	m_timeSinceLastShot = 0.f;
	UpdateAmmo(m_currentAmmo - 1);
}

void ShootingComponent::UpdateAmmo(const int newAmmo)
{
	m_currentAmmo = std::clamp(newAmmo, 0, m_maxAmmo);
	m_player->GetHud()->UpdateAmmo(m_currentAmmo);
}
