#pragma once
#include "entities/GameObject.hpp"

class CollisionComponent;
class Collider2D;

class WindowBounds : public GameObject {

public:
	WindowBounds(const char* name = "NA_WindowBounds");
	~WindowBounds() override {};

	const CollisionComponent* GetCollisionComponent() const { return m_collisionComponent; };

private:

	CollisionComponent* m_collisionComponent = nullptr;

};