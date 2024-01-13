#pragma once
#include "entities/GameObject.hpp"

class MovementComponent;
class CollisionComponent;
class WindowBounds;
class Collider2D;

class Meteor : public GameObject {

public:
	Meteor(const Transform& transform, const char* name = "NA_Meteor");
	Meteor(const Meteor& copy) = delete;
	const Meteor& operator=(const Meteor& other) = delete;
	~Meteor() override;

	void Update(const float deltaTime) override;

private:

	WindowBounds* m_windowBounds = nullptr;
	Collider2D* m_collider = nullptr;

	CollisionComponent* m_collisionComponent = nullptr;
	MovementComponent* m_movementComponent = nullptr;

};