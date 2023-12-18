#pragma once
#include <list>

#include "GameObject.hpp"
#include "CollisionComponent.hpp"
#include "Renderer.hpp"

class MovementComponent;
class Projectile;
class WindowBounds;
struct TextureResource;

class Player : public GameObject {

public:

	Player(const Transform& transform, TextureResource* texture, const char* name = "NA_Player");
	Player(const Player& copy) = delete;
	const Player& operator=(const Player& other) = delete;
	~Player() override;

	CollisionComponent* GetCollisionComponent() const { return m_collisionComponent; };
	MovementComponent* GetMovementComponent() const { return m_movementComponent; };

	void Update(const float deltaTime) override;
	void SetWindowBounds(WindowBounds* windowBounds);

private:
	void OnCollision(HitInformation& hitInformation);
	void ShootProjectile();

private:

	Vector2 m_velocity;
	Vector2 m_projectileSpawnPoint;
	WindowBounds* m_windowBounds;
	CollisionComponent* m_collisionComponent;
	MovementComponent* m_movementComponent;

	std::list<Projectile*> m_projectiles;
};
