#pragma once

#include "GameObject.hpp"
#include "CollisionComponent.hpp"

class MovementComponent;

class Projectile : public GameObject {

public:

	Projectile(const Transform& transform, TextureResource* texture, const char* name = "NA_Projectile");
	Projectile(const Projectile& copy) = delete;
	const Projectile& operator=(const Projectile& other) = delete;
	~Projectile() override;

	CollisionComponent* GetCollisionComponent() const { return m_collisionComponent; };
	MovementComponent* GetMovementComponent() const { return m_movementComponent; };

	void Update(const float deltaTime) override;

private:

	void OnCollision(HitInformation& hitInformation);

private:

	float m_distanceTraveled = 0.f;
	Vector2 m_startPosition;

	CollisionComponent* m_collisionComponent;
	MovementComponent* m_movementComponent;

};
