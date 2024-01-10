#include <SDL.h>
#include <iostream>

#include "entities/Player.hpp"
#include "components/MovementComponent.hpp"
#include "components/PlayerInputComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "entities/Projectile.hpp"
#include "entities/WindowBounds.hpp"
#include "utilities/ResourceManager.hpp"
#include "GameManager.hpp"


Player::Player(const Transform& transform, TextureResource* texture, const char* name)
	:
	GameObject(transform, texture, name),
	m_centerPoint((texture->GetDimensions().x / 2), (texture->GetDimensions().y / 2)),
	m_shootingSound("assets/shoot2.wav")
{
	m_transform.SetRotation(90.0);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetMaxSpeed(700.f);

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(false);
	m_collider = m_collisionComponent->AddCollider(texture->GetDimensions(), Vector2(0.5, 0.5), true, "Ship Collision");
	
	std::function<void(HitInfo&)> OnCollisionDelegate = std::bind(&Player::OnCollision, this, std::placeholders::_1);
	m_collider->SetCollisionDelegate(OnCollisionDelegate);

	m_inputComponent = AddComponent<PlayerInputComponent>(new PlayerInputComponent(this, "Input Component"));

}

Player::~Player()
{
	//std::cout << GetDisplayName() << " destroyed on Player destructor!\n";

}

void Player::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

	m_timeSinceLastShot += deltaTime;

	int mouseX = 0;
	int mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	const Vector2 mousePosition = Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	const Vector2 absoluteCenter = m_transform.GetPosition() + m_centerPoint;
	const Vector2 playerToMouse = mousePosition - absoluteCenter;
	m_isMouseFar = playerToMouse.Lenght() >= 40.f;
	if (m_isMouseFar) {

		const Vector2 currentDirection = Math::GetDirectionFromAngle(m_transform.GetRotation());
		const Vector2 desiredDirection = playerToMouse.Normalized();
		m_lookAtDirection = Math::Lerp(currentDirection, desiredDirection, 0.1f);

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

void Player::ShootProjectile()
{
	if (m_timeSinceLastShot < m_shootingReloadTime || !m_isMouseFar) {
		return;
	}

	assert(ResourceManager::projectileTexture);

	const Vector2 absoluteCenter = m_transform.GetPosition() + m_centerPoint;
	Vector2 spawnPosition(absoluteCenter - ResourceManager::projectileTexture->GetDimensions()/2.f + m_lookAtDirection * m_projetileSpawnDistance);
	const float angle = Math::GetAngleFromDirection(m_lookAtDirection);
	Transform spawnTransform = Transform(spawnPosition, angle);

	Projectile* projectile = new Projectile(spawnTransform, ResourceManager::projectileTexture, "Projectile");
	projectile->GetMovementComponent()->SetVelocity(m_lookAtDirection);
	projectile->GetBodyCollider()->ListenForCollisions(m_windowBounds->GetCollisionComponent()->GetAllColliders());

	GameManager::SpawnGameObject(projectile);

	m_shootingSound.PlaySound();
	
	m_timeSinceLastShot = 0.f;
}
