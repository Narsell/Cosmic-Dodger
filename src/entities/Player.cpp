#include <SDL.h>
#include <iostream>

#include "entities/Player.hpp"
#include "components/MovementComponent.hpp"
#include "components/PlayerInputComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/ShootingComponent.hpp"
#include "utilities/ResourceManager.hpp"
#include "utilities/GameState.hpp"
#include "entities/WindowBounds.hpp"
#include "GameManager.hpp"


Player::Player(HUD* hud, const char* name)
	:
	GameObject(Transform(), ResourceManager::playerTexture, name),
	m_hud(hud)
{
	
	Vector2 playerPosition(
		GameState::GetGameState()->GetPlayerStartPosition()
	);
	m_transform = Transform(playerPosition, 90.f);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetMaxSpeed(700.f);

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(false);
	m_collider = m_collisionComponent->AddCollider(ResourceManager::playerTexture->GetDimensions(), Vector2::ZERO, true, "Ship Collision");
	
	std::function<void(HitInfo&)> OnCollisionDelegate = std::bind(&Player::OnCollision, this, std::placeholders::_1);
	m_collider->SetCollisionDelegate(OnCollisionDelegate);

	m_inputComponent = AddComponent<PlayerInputComponent>(new PlayerInputComponent(this, "Input Component"));

	m_shootingComponent = AddComponent< ShootingComponent>(new ShootingComponent(this, "Shoot Component"));

}

Player::~Player()
{
	//std::cout << GetDisplayName() << " destroyed on Player destructor!\n";

}

HUD* Player::GetHud() const
{
	assert(m_hud);
	return m_hud;
}

WindowBounds* Player::GetWindowBounds() const
{
	assert(m_windowBounds);
	return m_windowBounds;
}

void Player::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	const Vector2 mousePosition = Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	const Vector2 absoluteCenter = m_transform.GetPosition() + GetCenterPoint();
	const Vector2 playerToMouse = mousePosition - absoluteCenter;
	m_isMouseOnPlayer = playerToMouse.Lenght() < 40.f;
	if (!m_isMouseOnPlayer) {

		const Vector2 currentDirection = Math::GetDirectionFromAngle(m_transform.GetRotation());
		const Vector2 desiredDirection = playerToMouse.Normalized();
		m_lookAtDirection = Math::Lerp(currentDirection, desiredDirection, 0.3f);

		m_transform.SetRotation(Math::GetAngleFromDirection(m_lookAtDirection));		
	}

	if (m_canMove && playerToMouse.Lenght() >= 120.f) {
		const float currentSpeed = m_movementComponent->GetSpeed();
		m_movementComponent->SetVelocity(m_lookAtDirection);
		m_movementComponent->SetSpeed(currentSpeed + 15);
	}
	else {
		const float currentSpeed = m_movementComponent->GetSpeed();
		m_movementComponent->SetSpeed(currentSpeed - 25);
	}
}

void Player::SetWindowBounds(WindowBounds* windowBounds)
{
	m_windowBounds = windowBounds;
	m_collider->ListenForCollisions(m_windowBounds->GetCollisionComponent()->GetAllColliders());
}

void Player::OnCollision(HitInfo& hitInformation)
{
}

