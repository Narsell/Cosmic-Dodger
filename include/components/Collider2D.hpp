#pragma once
#include <SDL.h>
#include <vector>

#include "Math.hpp"
#include "BaseEntity.hpp"

class Collider2D : public BaseEntity {
public:

	Collider2D();
	Collider2D(const Vector2& dimensions, const Vector2& relativePos = Vector2::ZERO, const bool renderBounds = false);
	~Collider2D();

	void Update(const float deltaTime) override;

	SDL_bool IsColliding(const Collider2D* other) const;
	SDL_bool IsColliding(const std::vector<Collider2D*> others) const;

	void SetbRenderBounds(const bool renderBounds) { bRenderBounds = renderBounds; };
	const bool GetbRenderBounds() const { return bRenderBounds; };
	const SDL_Rect& GetRect() const { return m_colliderRectangle; };

private:
	Vector2 m_position{ 0,0 };
	SDL_Rect m_colliderRectangle;
	bool bRenderBounds = false;

};
