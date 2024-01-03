#include <SDL.h>
#include <iostream>

#include "Player.hpp"
#include "GameManager.hpp"
#include "MovementComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "Projectile.hpp"
#include "Window.hpp"
#include "WindowBounds.hpp"
#include "Window.hpp"


Player::Player(const Transform& transform, TextureResource* texture, const char* name)
	:
	GameObject(transform, texture, name),
	m_centerPoint((texture->GetDimensions().x / 2), (texture->GetDimensions().y / 2))
{
	m_transform.SetRotation(90.0);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetMaxSpeed(500.f);
	m_movementComponent->SetRotationFollowsVelocity(true);

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
	m_mouseCheck = playerToMouse.Lenght() >= 50.f;
	if (m_mouseCheck) {
		const float currentSpeed = m_movementComponent->GetSpeed();
		const Vector2 currentVelocity = Math::GetDirectionFromAngle(m_transform.GetRotation()) * ((currentSpeed > 0.f) ? currentSpeed : 1.f);
		currentVelocity.Print();
		const Vector2 desiredVelocity = playerToMouse.Normalized() * ((currentSpeed > 0.f) ? currentSpeed : 1.f);
		const Vector2 difference = desiredVelocity - currentVelocity;
		const Vector2 newDirection = (difference * 0.1f + currentVelocity);
		m_lookAtDirection = newDirection.Normalized();
		
		m_movementComponent->SetVelocity(newDirection.Normalized());
		
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
	if (m_timeSinceLastShot < 0.15f || !m_mouseCheck) {
		return;
	}

	assert(Window::projectileTexture);

	const Vector2 absoluteCenter = m_transform.GetPosition() + m_centerPoint;
	Vector2 spawnPosition(absoluteCenter - Window::projectileTexture->GetDimensions()/2.f + m_lookAtDirection * m_projetileSpawnDistance);
	const float angle = Math::GetAngleFromDirection(m_lookAtDirection);
	Transform spawnTransform = Transform(spawnPosition, angle);

	Projectile* projectile = new Projectile(spawnTransform, Window::projectileTexture, "Projectile");
	projectile->GetMovementComponent()->SetVelocity(m_lookAtDirection);
	projectile->GetBodyCollider()->ListenForCollisions(m_windowBounds->GetCollisionComponent()->GetAllColliders());

	GameManager::SpawnGameObject(projectile);

	m_timeSinceLastShot = 0.f;
}
