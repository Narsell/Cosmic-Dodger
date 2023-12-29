#pragma once
#include "GameObject.hpp"

class CollisionComponent;
class Collider2D;

class WindowBounds : public GameObject {

public:
	WindowBounds(const char* name = "NA_WindowBounds");
	WindowBounds(const WindowBounds& copy) = delete;
	const WindowBounds& operator=(const WindowBounds& other) = delete;
	~WindowBounds() {};

	const CollisionComponent* GetCollisionComponent() const { return m_collisionComponent; };

private:

	CollisionComponent* m_collisionComponent = nullptr;

};