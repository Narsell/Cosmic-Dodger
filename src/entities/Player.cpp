#include <SDL.h>
#include <iostream>

#include "Player.hpp"
#include "GameManager.hpp"
#include "MovementComponent.hpp"
#include "Projectile.hpp"
#include "RenderWindow.hpp"


Player::Player(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions, const char* name)
	:
	GameObject(position, texture, textureDimensions, name)
{
	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->AddCollider(textureDimensions, Vector2::ZERO, true, "Ship Collision");
	m_collisionComponent->SetCanRender(true);

	std::function<void(HitInformation&)> OnCollisionDelegate = std::bind(&Player::OnCollision, this, std::placeholders::_1);
	m_collisionComponent->SetCollisionDelegate(OnCollisionDelegate);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
}

Player::~Player()
{
	std::cout << GetDisplayName() << " destroyed on Player destructor!\n";

	for (Projectile* projectile : m_projectiles) {
		delete projectile;
	}
}

void Player::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

	//Handle events
	for (SDL_Event &frameEvent : GameManager::GetFrameEvents()) {
		if (frameEvent.type == SDL_KEYDOWN && frameEvent.key.keysym.sym == SDLK_SPACE) {
			ShootProjectile();
		}
	}
}

void Player::OnCollision(HitInformation& hitInformation)
{
	if (hitInformation.hitCollider->GetDisplayName() == "UP"
		|| hitInformation.hitCollider->GetDisplayName() == "DOWN") 
	{
		m_velocity = Vector2(m_velocity.x, -m_velocity.y);
	}
	else if (hitInformation.hitCollider->GetDisplayName() == "LEFT"
		|| hitInformation.hitCollider->GetDisplayName() == "RIGHT") {
		m_velocity = Vector2(-m_velocity.x, m_velocity.y);
	}

}

void Player::ShootProjectile()
{
	std::cout << "SHOOT!\n";
	assert(RenderWindow::projectileTexture);

	Projectile* projectile = new Projectile(m_position, RenderWindow::projectileTexture, Vector2(48, 46));
	projectile->SetVelocity(Vector2(0, -5));
	m_projectiles.emplace_back(
		GameManager::SpawnGameObject(projectile)
	);

}
