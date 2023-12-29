#pragma once
#include <SDL.h>
#include <vector>
#include <functional>

#include "Math.hpp"
#include "Component.hpp"
#include "Collider2D.hpp"
#include "GameObject.hpp"


class Collider2D;

class CollisionComponent : public Component {

public:

	CollisionComponent(GameObject* parent, const char* name = "NA_CollisionComponent");
	~CollisionComponent();

	Collider2D* AddCollider(const Vector2& dimensions, const Vector2& relativePos = Vector2::ZERO, const bool visible = false, const char* name="Collider2D");

	Collider2D* GetColliderByIndex(const size_t index) const { return m_colliders.at(index); };
	const std::vector<Collider2D*> GetAllColliders() const { return m_colliders; };

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

	virtual void SetCanUpdate(const bool canUpdate) override;

	const Vector2& GetPosition() const { return m_position; };

private:

	Vector2 m_position;
	std::vector<Collider2D*> m_colliders;
};