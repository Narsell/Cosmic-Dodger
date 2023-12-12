#pragma once

#include "GameObject.hpp"
#include "CollisionComponent.hpp"

class MovementComponent;

class Projectile : public GameObject {

public:

	Projectile(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions, const char* name = "NA_Projectile");
	Projectile(const Projectile& copy) = delete;
	const Projectile& operator=(const Projectile& other) = delete;
	~Projectile() override;

	CollisionComponent* GetCollisionComponent() const { return m_collisionComponent; };
	MovementComponent* GetMovementComponent() const { return m_movementComponent; };

	void Update(const float deltaTime) override;

private:

	void OnCollision(HitInformation& hitInformation);

	CollisionComponent* m_collisionComponent;
	MovementComponent* m_movementComponent;

};
