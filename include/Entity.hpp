#pragma once
#include <SDL.h>
#include <vector>

#include "Math.hpp"

class Collider2D;

class Entity 
{
public:
	Entity(const Vector2& position, SDL_Texture* texture);
	Entity(const Entity& copy) = delete;
	const Entity& operator=(const Entity& other) = delete;
	~Entity();
	
	//Updates and "physics"
	void Update();
	void AddPositionDelta(const Vector2& deltaPosition);
	void SetVelocity(const Vector2& newVelocity) { m_velocity = newVelocity; };

	//Collisions
	void AddCollider(const Vector2& dimensions, const Vector2& relativePos = Vector2::ZERO, const bool renderBounds = false);
	const bool HasCollided(const Entity& otherEntity);

	// Getters
	const Vector2& GetPosition() const { return m_position; };
	const Vector2& GetVelocity() const { return m_velocity; };
	SDL_Texture* GetTexture() const { return m_texture; };
	SDL_Rect GetCurrentFrame() const { return m_currentFrame; };
	const std::vector<Collider2D*> GetAllColliders() const { return m_colliders; };
	const Collider2D& GetColliderByIndex(const size_t index) const { return *m_colliders.at(index); };

private:

	Vector2 m_position;
	Vector2 m_velocity;
	SDL_Rect m_currentFrame;
	SDL_Texture* m_texture = nullptr;
	std::vector<Collider2D*> m_colliders;

};
