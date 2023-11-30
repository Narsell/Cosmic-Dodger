#include <SDL.h>
#include <iostream>

#include "Player.hpp"
#include "GameManager.hpp"


Player::Player(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions)
	:GameObject(position, texture, textureDimensions)
{
	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this));
}

Player::~Player()
{
}

void Player::Update(const float deltaTime)
{
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