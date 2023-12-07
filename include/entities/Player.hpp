#pragma once
#include "GameObject.hpp"
#include "CollisionComponent.hpp"

class CollisionComponent;

class Player : public GameObject {

public:

	Player(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions, const char* name = "NA_Player");
	Player(const Player& copy) = delete;
	const Player& operator=(const Player& other) = delete;
	~Player();

	CollisionComponent* GetCollisionComponent() const { return m_collisionComponent; };

	//TODO: Upgrade this to components
	virtual void AddPositionDelta(const Vector2& deltaPosition);
	virtual void SetVelocity(const Vector2& newVelocity) { m_velocity = newVelocity; };

	void Update(const float deltaTime) override;

private:

	void OnCollision(HitInformation& hitInformation);

	class CollisionComponent* m_collisionComponent;
};
