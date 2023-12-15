#include <SDL.h>
#include <iostream>

#include "Player.hpp"
#include "GameManager.hpp"
#include "MovementComponent.hpp"
#include "Projectile.hpp"
#include "RenderWindow.hpp"


Player::Player(const Transform& transform, SDL_Texture* texture, const Vector2& textureDimensions, const char* name)
	:
	GameObject(transform, texture, textureDimensions, name),
	projectileSpawnOffset(textureDimensions.x/2, -50)
{
	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->AddCollider(textureDimensions, Vector2::ZERO, true, "Ship Collision");
	m_collisionComponent->SetCanRender(true);

	std::function<void(HitInformation&)> OnCollisionDelegate = std::bind(&Player::OnCollision, this, std::placeholders::_1);
	m_collisionComponent->SetCollisionDelegate(OnCollisionDelegate);

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
		if (frameEvent.type == SDL_KEYDOWN)
		{
			SDL_Keycode pressedKey = frameEvent.key.keysym.sym;
			if (pressedKey == SDLK_SPACE) {
				ShootProjectile();
			}

			if (pressedKey == SDLK_d) {
				velocity = Vector2::RIGHT * 5; 
			}
			else if (pressedKey == SDLK_a) {
				velocity = Vector2::LEFT * 5;
			}
			
		}
		else if (frameEvent.type == SDL_KEYUP && frameEvent.key.keysym.sym != SDLK_SPACE) {
			velocity = Vector2::ZERO;
		}
	}

	m_movementComponent->AddPositionDelta(velocity);
}

void Player::OnCollision(HitInformation& hitInformation)
{
	if (hitInformation.hitGameObject->GetDisplayName() == "Window Bounds") {
		m_transform.SetPosition(hitInformation.hitLocation);
	}

}

void Player::ShootProjectile()
{
	std::cout << "SHOOT!\n";
	assert(RenderWindow::projectileTexture);
	Vector2 projectileTextureDim(48, 46);
	Vector2 projectileTextOffset(projectileTextureDim.x / 2, 0);
	Transform spawnTransform = Transform(m_transform.GetPosition() + projectileSpawnOffset - projectileTextOffset, -90.f);
	Projectile* projectile = new Projectile(spawnTransform, RenderWindow::projectileTexture, projectileTextureDim);
	m_projectiles.emplace_back(
		GameManager::SpawnGameObject(projectile)
	);

}
