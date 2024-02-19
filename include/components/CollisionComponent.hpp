#pragma once
#include <vector>

#include "utilities/Math.hpp"
#include "components/Transform.hpp"
#include "components/Component.hpp"

class Collider2D;
class GameObject;

class CollisionComponent : public Component {

public:

	CollisionComponent(GameObject* parent, const char* name = "NA_CollisionComponent");
	~CollisionComponent() override;

	Transform m_transform;
	
	Collider2D* AddCollider(const Vector2& dimensions, const Vector2& relativePos = Vector2::ZERO, const bool visible = false, const char* name="Collider2D");

	Collider2D* GetColliderByIndex(const size_t index) const { return m_colliders.at(index); };
	const std::vector<Collider2D*> GetAllColliders() const { return m_colliders; };

	virtual void Render(SDL_Renderer* renderer) override;
	virtual void Update(const float deltaTime) override;

	virtual void SetCanUpdate(const bool canUpdate) override;


private:

	std::vector<Collider2D*> m_colliders;
};