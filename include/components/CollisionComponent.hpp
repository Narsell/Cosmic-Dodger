#pragma once
#include <SDL.h>
#include <vector>
#include <functional>

#include "Math.hpp"
#include "Component.hpp"
#include "Collider2D.hpp"
#include "GameObject.hpp"

struct HitInformation {

	HitInformation():
		hasHit(false),
		hitLocation(Vector2::ZERO),
		hitCollider(nullptr),
		hitGameObject(nullptr)
	{}

	void Print() const {
		std::cout << "HitInformation:\n"
			"\tCollision: " << hasHit << "\n"
			"\tLocation: (" << hitLocation.x << "," << hitLocation.y << ")\n"
			"\tCollider: " << hitCollider->GetDisplayName() << "\n"
			"\tObject: " << hitGameObject->GetDisplayName() << "\n"
			<< "===========================================\n";
	}

	bool hasHit;
	Vector2 hitLocation;
	class Collider2D* hitCollider;
	GameObject* hitGameObject;
};

class Collider2D;

class CollisionComponent : public Component {

public:

	CollisionComponent(class GameObject* parent, const char* name = "NA_CollisionComponent");
	~CollisionComponent();

	void AddCollider(const Vector2& dimensions, const Vector2& relativePos = Vector2::ZERO, const bool visible = false, const char* name="Collider2D");
	void ListenForCollisions(CollisionComponent* collisionCandidate);
	void SetCollisionDelegate(std::function<void(HitInformation&)> delegate);

	const Collider2D* GetColliderByIndex(const size_t index) const { return m_colliders.at(index); };
	const std::vector<Collider2D*> GetAllColliders() const { return m_colliders; };

	//GameObject* OnCollision() const;

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

	const Vector2& GetPosition() const { return m_position; };

private:

	Vector2 m_position;
	std::vector<Collider2D*> m_colliders;
	std::vector<CollisionComponent*> m_collisionCandidates;
	HitInformation lastHitInformation;
	std::function<void(HitInformation&)> OnCollisionDelegate;

};