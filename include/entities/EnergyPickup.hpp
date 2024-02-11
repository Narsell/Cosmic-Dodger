#pragma once
#include "entities/GameObject.hpp"
#include "components/Collider2D.hpp"
#include "components/Sound.hpp"

class CollisionComponent;

class EnergyPickup : public GameObject {

public:

	EnergyPickup(const Transform& transform, const char* name = "NA_FuelGrab");
	~EnergyPickup() override;

	void Update(const float deltaTime) override;

private:

	void OnCollision(HitInfo& hitInfo);
	void BounceAnimation(const float deltaTime);

private:

	const float m_maxFloatingDistance = 10.f;
	Vector2 m_startPosition;
	Vector2 m_velocity;

	CollisionComponent* m_collisionComponent = nullptr;
	Collider2D* m_collider = nullptr;

	Sound m_pickUpSound;

};