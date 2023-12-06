#pragma once
#include "GameObject.hpp"

class WindowBounds : public GameObject {

public:
	WindowBounds(const Vector2& windowDimensions, const char* name = "NA_WindowBounds");
	WindowBounds(const WindowBounds& copy) = delete;
	const WindowBounds& operator=(const WindowBounds& other) = delete;
	~WindowBounds() {};

private:
	class CollisionComponent* m_collisionComponent;

};