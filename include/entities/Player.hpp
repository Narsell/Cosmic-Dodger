#pragma once
#include <list>

#include "GameObject.hpp"
#include "CollisionComponent.hpp"

class MovementComponent;
class Projectile;

class Player : public GameObject {

public:

	Player(const Transform& position, SDL_Texture* texture, const Vector2& textureDimensions, const char* name = "NA_Player");
	Player(const Player& copy) = delete;
	const Player& operator=(const Player& other) = delete;
	~Player() override;

	CollisionComponent* GetCollisionComponent() const { return m_collisionComponent; };
	MovementComponent* GetMovementComponent() const { return m_movementComponent; };

	void Update(const float deltaTime) override;

private:

	Vector2 velocity;
	Vector2 projectileSpawnOffset;

	void OnCollision(HitInformation& hitInformation);
	void ShootProjectile();

	CollisionComponent* m_collisionComponent;
	MovementComponent* m_movementComponent;

	std::list<Projectile*> m_projectiles;
};
