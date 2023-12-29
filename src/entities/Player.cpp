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
	m_projectileSpawnPoint((texture->GetDimensions().x / 2) - 5, -20)
{
	m_transform.SetRotation(90.0);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetSpeed(500.f);
	m_movementComponent->SetRotationFollowsVelocity(false);

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(false);
	m_collider = m_collisionComponent->AddCollider(texture->GetDimensions(), Vector2::ZERO, true, "Ship Collision");
	
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
}

void Player::SetWindowBounds(WindowBounds* windowBounds)
{
	m_windowBounds = windowBounds;
	m_collider->ListenForCollisions(m_windowBounds->GetCollisionComponent()->GetAllColliders());
}

void Player::OnCollision(HitInfo& hitInformation)
{

}

void Player::ShootProjectile() const
{
	assert(Window::projectileTexture);

	int mouseX = 0;
	int mouseY = 0;

	SDL_GetMouseState(&mouseX, &mouseY);
	const Vector2 mousePosition = Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	const Vector2 spawnPosition = m_transform.GetPosition() + m_projectileSpawnPoint;
	const Vector2 velocity = (mousePosition - spawnPosition).Normalized();
	const double angle = Math::GetAngleFromDirection(velocity);

	Transform spawnTransform = Transform(spawnPosition, angle);

	Projectile* projectile = new Projectile(spawnTransform, Window::projectileTexture, "Projectile");
	projectile->GetMovementComponent()->SetVelocity(velocity);
	projectile->GetBodyCollider()->ListenForCollisions(m_windowBounds->GetCollisionComponent()->GetAllColliders());

	GameManager::SpawnGameObject(projectile);
}
