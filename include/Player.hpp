#pragma once
#include "Entity.hpp"


class Player : public Entity {

public:

	Player(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions);
	Player(const Player& copy) = delete;
	const Player& operator=(const Player& other) = delete;
	~Player();

	void Update(const float deltaTime) override;

};
