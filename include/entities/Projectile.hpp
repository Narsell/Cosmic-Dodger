#pragma once

#include "entities/GameObject.hpp"
#include "components/Collider2D.hpp"

class MovementComponent;
class CollisionComponent;
class WindowBounds;


class Projectile : public GameObject {

public:

	Projectile(const Transform& transform, const char* name = "NA_Projectile");
	Projectile(const Projectile& copy) = delete;
	const Projectile& operator=(const Projectile& other) = delete;
	~Projectile() override;

	Collider2D* GetBodyCollider() const { return m_collider; };

	CollisionComponent* GetCollisionComponent() const { return m_collisionComponent; };
	MovementComponent* GetMovementComponent() const { return m_movementComponent; };

	void SetWindowCollisions(WindowBounds* windowBounds);

	void Update(const float deltaTime) override;

private:

	void OnCollision(HitInfo& hitInformation);

private:

	Collider2D* m_collider = nullptr;

	std::uint8_t m_bouncesCounter = 0;
	std::uint8_t m_maxBounces = 1;

	float m_distanceTraveled = 0.f;
	Vector2 m_startPosition;

	CollisionComponent* m_collisionComponent;
	MovementComponent* m_movementComponent;

};
