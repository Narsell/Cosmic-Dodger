#include <SDL.h>
#include <iostream>

#include "Player.hpp"
#include "GameManager.hpp"
#include "MovementComponent.hpp"
#include "Projectile.hpp"
#include "Renderer.hpp"
#include "WindowBounds.hpp"
#include "Renderer.hpp"


Player::Player(const Transform& transform, TextureResource* texture, const char* name)
	:
	GameObject(transform, texture, name),
	m_projectileSpawnPoint(texture->GetDimensions().x / 2, -50),
	m_windowBounds(nullptr)
{
	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->AddCollider(texture->GetDimensions(), Vector2::ZERO, true, "Ship Collision");
	m_collisionComponent->SetCanRender(true);

	std::function<void(HitInformation&)> OnCollisionDelegate = std::bind(&Player::OnCollision, this, std::placeholders::_1);
	m_collisionComponent->SetCollisionDelegate(OnCollisionDelegate);

}

Player::~Player()
{
	//std::cout << GetDisplayName() << " destroyed on Player destructor!\n";

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
				m_velocity = Vector2::RIGHT * 5; 
			}
			else if (pressedKey == SDLK_a) {
				m_velocity = Vector2::LEFT * 5;
			}
			
		}
		else if (frameEvent.type == SDL_KEYUP && frameEvent.key.keysym.sym != SDLK_SPACE) {
			m_velocity = Vector2::ZERO;
		}
	}

	m_movementComponent->AddPositionDelta(m_velocity);
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

	Vector2 projectileOffset(Renderer::projectileTexture->GetDimensions().x / 2, 0);
	Transform spawnTransform = Transform(m_transform.GetPosition() + m_projectileSpawnPoint - projectileOffset, -90.f);

	Projectile* projectile = new Projectile(spawnTransform, Renderer::projectileTexture);
	projectile->GetCollisionComponent()->ListenForCollisions(m_windowBounds);
	m_projectiles.emplace_back(
		GameManager::SpawnGameObject(projectile)
	);

}
