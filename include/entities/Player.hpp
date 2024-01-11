#pragma once
#include <list>

#include "entities/GameObject.hpp"
#include "components/Collider2D.hpp"
#include "Window.hpp"

class MovementComponent;
class PlayerInputComponent;
class CollisionComponent;
class ShootingComponent;
class WindowBounds;
class HUD;
struct TextureResource;

class Player : public GameObject {

public:

	Player(const Transform& transform, TextureResource* texture, HUD* hud, const char* name = "NA_Player");
	Player(const Player& copy) = delete;
	const Player& operator=(const Player& other) = delete;
	~Player() override;

	const bool GetIsMouseOnPlayer() const { return m_isMouseOnPlayer; };
	HUD* GetHud() const;
	WindowBounds* GetWindowBounds() const;

	CollisionComponent* GetCollisionComponent() const { return m_collisionComponent; };
	MovementComponent* GetMovementComponent() const { return m_movementComponent; };
	ShootingComponent* GetShootingComponent() const { return m_shootingComponent; };

	void SetWindowBounds(WindowBounds* windowBounds);
	void SetCanMove(const bool canMove) { m_canMove = canMove; };

	void Update(const float deltaTime) override;

private:
	void OnCollision(HitInfo& hitInformation);

private:

	bool m_isMouseOnPlayer = true;
	Vector2 m_lookAtDirection = Vector2::ZERO;
	bool m_canMove = false;

	WindowBounds* m_windowBounds = nullptr;
	Collider2D* m_collider = nullptr;

	CollisionComponent* m_collisionComponent = nullptr;
	MovementComponent* m_movementComponent = nullptr;
	PlayerInputComponent* m_inputComponent = nullptr;
	ShootingComponent* m_shootingComponent = nullptr;

	HUD* m_hud;

};
