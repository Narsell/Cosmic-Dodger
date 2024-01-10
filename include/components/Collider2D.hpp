#pragma once
#include <SDL.h>
#include <vector>
#include <functional>

#include "utilities/Math.hpp"
#include "entities/BaseEntity.hpp"
#include "entities/GameObject.hpp"

class CollisionComponent;

struct HitInfo {

	HitInfo() :
		hasHit(false),
		hitLocation(Vector2::ZERO),
		hitCollider(nullptr),
		hitGameObject(nullptr)
	{}

	void Print() const;

	bool hasHit;
	Vector2 hitLocation;
	class Collider2D* hitCollider;
	GameObject* hitGameObject;
};

class Collider2D : public BaseEntity {
public:

	Collider2D(const Vector2& dimensions, CollisionComponent* parentComp, const Vector2& relativePos = Vector2::ZERO, const bool visible = false, const char* name = "NA_Collider");
	~Collider2D();


	void Render(SDL_Renderer* renderer) override;
	void Update(const float deltaTime) override;

	void ListenForCollisions(Collider2D* collisionCandidate);
	void ListenForCollisions(std::vector<Collider2D*> newCollisionCandidates);
	void SetCollisionDelegate(std::function<void(HitInfo&)> delegate);
	bool IsColliding(Collider2D* other, HitInfo& OutHitInformation) const;

	const SDL_FRect& GetRect() const { return m_colliderRectangle; };

private:
	Transform m_absTransform;
	Transform m_relTransform;
	SDL_FRect m_colliderRectangle;
	CollisionComponent* m_parentComponent = nullptr;
	std::function<void(HitInfo&)> OnCollisionDelegate;
	std::vector<Collider2D*> m_collisionCandidates;
	HitInfo m_lastHitInformation;

};
