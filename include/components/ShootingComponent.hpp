#pragma once
#include "Component.hpp"
#include "entities/GameObject.hpp"
#include "components/Sound.hpp"

class Player;
class HUD;

class ShootingComponent : public Component {

public:

	ShootingComponent(GameObject* parent, const char* name = "NA_CollisionComponent");
	~ShootingComponent() override;

	//Resets current ammo and shooting timers
	void Reset();

	static constexpr int GetMaxAmmo() { return s_maxAmmo; };
	const int GetCurrentAmmo() const { return m_currentAmmo; };

	virtual void Update(const float deltaTime) override;

	void Shoot();

private:
	void UpdateAmmo(const int newAmmo);

private:
	Sound m_shootingSound;
	float m_timeSinceLastShot = 0.f;
	const float m_shootingReloadTime = 0.15f;
	const float m_projetileSpawnDistance = 50.f;
	static constexpr int s_maxAmmo = 20;
	int m_currentAmmo = s_maxAmmo;
	float m_timeSinceLastReplenish = 0.f;
	const float m_increaseAmmoTime = 2.f;

	Player* m_player;
	HUD* m_hud = nullptr;

};