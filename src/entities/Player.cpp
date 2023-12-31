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
	m_movementComponent->SetSpeed(500.f);
	m_movementComponent->SetRotationFollowsVelocity(false);

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(true);
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
	timeSinceLastShot += deltaTime;

	int mouseX = 0;
	int mouseY = 0;

	SDL_GetMouseState(&mouseX, &mouseY);
	const Vector2 mousePosition = Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	const Vector2 spawnPosition = m_transform.GetPosition() + m_centerPoint;
	const Vector2 direction = (mousePosition - spawnPosition).Normalized();
	const float angle = Math::GetAngleFromDirection(direction);
	m_transform.SetRotation(angle);

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
	if (timeSinceLastShot < 0.15f) {
		return;
	}

	assert(Window::projectileTexture);

	int mouseX = 0;
	int mouseY = 0;

	SDL_GetMouseState(&mouseX, &mouseY);
	const Vector2 mousePosition = Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	Vector2 absoluteCenter = m_transform.GetPosition() + m_centerPoint;

	const Vector2 direction = (mousePosition - absoluteCenter).Normalized();
	const float angle = Math::GetAngleFromDirection(direction);

	Vector2 spawnPosition(absoluteCenter - Window::projectileTexture->GetDimensions()/2.f + direction*50.f);
	Transform spawnTransform = Transform(spawnPosition, angle);

	Projectile* projectile = new Projectile(spawnTransform, Window::projectileTexture, "Projectile");
	projectile->GetMovementComponent()->SetVelocity(direction);
	projectile->GetBodyCollider()->ListenForCollisions(m_windowBounds->GetCollisionComponent()->GetAllColliders());

	GameManager::SpawnGameObject(projectile);

	timeSinceLastShot = 0.f;
}
