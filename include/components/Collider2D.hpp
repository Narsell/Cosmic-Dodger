#pragma once
#include <SDL.h>
#include <vector>

#include "Math.hpp"
#include "BaseEntity.hpp"

class CollisionComponent;
struct HitInformation;

class Collider2D : public BaseEntity {
public:

	Collider2D(const Vector2& dimensions, CollisionComponent* parentComp, const Vector2& relativePos = Vector2::ZERO, const bool visible = false, const char* name = "NA_Collider");
	~Collider2D();

	void Render(SDL_Renderer* renderer) override;
	void Update(const float deltaTime) override;

	bool IsColliding(Collider2D* other, HitInformation& OutHitInformation) const;
	bool IsColliding(const std::vector<Collider2D*> others, HitInformation& OutHitInformation) const;

	const SDL_FRect& GetRect() const { return m_colliderRectangle; };

private:
	Vector2 m_position{ 0,0 };
	SDL_FRect m_colliderRectangle;
	CollisionComponent* m_parentComponent = nullptr;

};
