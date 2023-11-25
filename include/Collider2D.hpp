#pragma once
#include <SDL.h>
#include "Math.hpp"

class Collider2D {
public:
	Collider2D();
	Collider2D(const Vector2& dimensions, const Vector2& relativePos = Vector2::ZERO, const bool renderBounds = false);
	~Collider2D();

	void Update(const class Entity* parent);
	SDL_bool IsColliding(const Collider2D& other) const;


	void SetbRenderBounds(const bool renderBounds) { bRenderBounds = renderBounds; };
	const bool GetbRenderBounds() const { return bRenderBounds; };
	const SDL_Rect& GetRect() const { return m_colliderRectangle; };

private:
	Vector2 m_position{0,0};
	SDL_Rect m_colliderRectangle;
	bool bRenderBounds = false;

};