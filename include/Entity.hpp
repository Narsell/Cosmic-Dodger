#pragma once
#include <SDL.h>

#include "Math.hpp"

class Collider2D;

class Entity 
{
public:
	Entity(const Vector2& position, SDL_Texture* texture);
	~Entity();
	
	void Update();
	void AddPositionDelta(const Vector2& deltaPosition);
	const Vector2& GetPosition() const { return m_position; };
	SDL_Texture* GetTexture() const { return m_texture; };
	SDL_Rect GetCurrentFrame() const { return m_currentFrame; };
	const Collider2D& GetCollider2D() const { return *m_collider; };

private:

	Vector2 m_position;
	SDL_Rect m_currentFrame;
	SDL_Texture* m_texture = nullptr;
	Collider2D* m_collider = nullptr;

};
