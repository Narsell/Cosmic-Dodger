#pragma once
#include <SDL.h>
#include <vector>

#include "Math.hpp"
#include "Component.hpp"

class Collider2D;

class CollisionComponent : public Component {

public:

	CollisionComponent(class GameObject* parent);

	void AddCollider(const Vector2& dimensions, const Vector2& relativePos = Vector2::ZERO, const bool renderBounds = false);
	Collider2D* GetColliderByIndex(const size_t index) const { return m_colliders.at(index); };
	const std::vector<Collider2D*> GetAllColliders() const { return m_colliders; };

	//GameObject* OnCollision() const;

	void Update(const float deltaTime) override;

private:

	Vector2 m_position;
	std::vector<Collider2D*> m_colliders;

};