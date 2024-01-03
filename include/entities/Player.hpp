#pragma once
#include <list>

#include "GameObject.hpp"
#include "CollisionComponent.hpp"
#include "Window.hpp"

class MovementComponent;
class PlayerInputComponent;
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
	void ShootProjectile();
	void SetCanMove(const bool canMove) { m_canMove = canMove; };

private:
	void OnCollision(HitInfo& hitInformation);

private:

	const float m_shootingReloadTime = 0.15f;
	float m_timeSinceLastShot = 0.f;
	const float m_projetileSpawnDistance = 50.f;
	//True if the mouse is out of the player bounds to avoid unexpected behavior.
	bool m_isMouseFar = true;

	Vector2 m_lookAtDirection = Vector2::ZERO;
	Vector2 m_centerPoint = Vector2::ZERO;
	bool m_canMove = false;

	WindowBounds* m_windowBounds = nullptr;
	Collider2D* m_collider = nullptr;

	CollisionComponent* m_collisionComponent = nullptr;
	MovementComponent* m_movementComponent = nullptr;
	PlayerInputComponent* m_inputComponent = nullptr;

};
