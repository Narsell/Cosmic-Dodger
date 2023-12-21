#include <SDL.h>
#include <iostream>

#include "Player.hpp"
#include "GameManager.hpp"
#include "MovementComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "Projectile.hpp"
#include "Renderer.hpp"
#include "WindowBounds.hpp"
#include "Renderer.hpp"


Player::Player(const Transform& transform, TextureResource* texture, const char* name)
	:
	GameObject(transform, texture, name),
	m_projectileSpawnPoint((texture->GetDimensions().x / 2) - 5, -20),
	m_windowBounds(nullptr)
{
	m_transform.SetRotation(90.0);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetSpeed(5.f);
	m_movementComponent->SetRotationFollowsVelocity(false);

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->AddCollider(texture->GetDimensions(), Vector2::ZERO, true, "Ship Collision");
	m_collisionComponent->SetCanRender(false);

	std::function<void(HitInformation&)> OnCollisionDelegate = std::bind(&Player::OnCollision, this, std::placeholders::_1);
	m_collisionComponent->SetCollisionDelegate(OnCollisionDelegate);

	m_inputComponent = AddComponent<PlayerInputComponent>(new PlayerInputComponent(this, "Input Component"));

}

Player::~Player()
{
	//std::cout << GetDisplayName() << " destroyed on Player destructor!\n";

}

void Player::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Player::SetWindowBounds(WindowBounds* windowBounds)
{
	m_windowBounds = windowBounds;
	m_collisionComponent->ListenForCollisions(m_windowBounds);
}

void Player::OnCollision(HitInformation& hitInformation)
{
	if (hitInformation.hitGameObject->GetDisplayName() == "Window Bounds") {
		m_transform.SetPosition(hitInformation.hitLocation);
	}
}

void Player::ShootProjectile()
{
	assert(Renderer::projectileTexture);

	int* mouseX = new int(0);
	int* mouseY = new int(0);

	SDL_GetMouseState(mouseX, mouseY);
	const Vector2 mousePosition = Vector2(static_cast<float>(*mouseX), static_cast<float>(*mouseY));
	const Vector2 spawnPosition = m_transform.GetPosition() + m_projectileSpawnPoint;
	const Vector2 velocity = (mousePosition - spawnPosition).Normalized();
	const double angle = Math::GetAngleFromDirection(velocity);

	Transform spawnTransform = Transform(spawnPosition, angle);

	Projectile* projectile = new Projectile(spawnTransform, Renderer::projectileTexture, "Projectile");
	projectile->GetMovementComponent()->SetVelocity(velocity);
	//projectile->GetCollisionComponent()->ListenForCollisions(m_windowBounds);

	m_projectiles.emplace_back(
		GameManager::SpawnGameObject(projectile)
	);

}
