#include <SDL.h>
#include <iostream>

#include "Player.hpp"
#include "GameManager.hpp"
#include "CollisionComponent.hpp"


Player::Player(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions, const char* name)
	:
	GameObject(position, texture, textureDimensions, name)
{
	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->AddCollider(Vector2(112, 75), Vector2::ZERO, true, "Ship Collision");
	m_collisionComponent->AddCollider(Vector2(10, 10), Vector2(51, -20), false, "Projectile Collision");

	m_collisionComponent->SetCanRender(true);
}

Player::~Player()
{
	std::cout << GetDisplayName() << " destroyed on Player destructor!\n";

}

void Player::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

	AddPositionDelta(m_velocity);

	//Handle events
	for (SDL_Event &frameEvent : GameManager::GetFrameEvents()) {
		if (frameEvent.type == SDL_KEYDOWN && frameEvent.key.keysym.sym == SDLK_SPACE) {
			std::cout << "SHOOT!\n";
		}
	}

	m_collisionComponent->Update(deltaTime);
}

void Player::AddPositionDelta(const Vector2& deltaPosition)
{
	m_position += deltaPosition;
}