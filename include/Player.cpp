#include <SDL.h>
#include <iostream>

#include "Player.hpp"
#include "GameManager.hpp"


Player::Player(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions)
	:Entity(position, texture, textureDimensions)
{
}

Player::~Player()
{
}

void Player::Update(const float deltaTime)
{
	Entity::Update(deltaTime);

	for (SDL_Event &frameEvent : GameManager::GetFrameEvents()) {
		if (frameEvent.type == SDL_KEYDOWN && frameEvent.key.keysym.sym == SDLK_SPACE) {
			std::cout << "SHOOT!\n";
		}
	}
}
