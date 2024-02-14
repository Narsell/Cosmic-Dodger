#pragma once
#include "entities/GameObject.hpp"
#include "components/Collider2D.hpp"

class MovementComponent;
class CollisionComponent;
class WindowBounds;
class Collider2D;
class MeteorSpawner;

class Meteor : public GameObject {

public:
	Meteor(const Transform& transform, const Vector2& initialVelocity, const float speed, const char* name = "NA_Meteor");
	~Meteor() override;

	void Update(const float deltaTime) override;
	static const float GetMaxSpeed() { return maxSpeed; };

private:

	void OnCollision(HitInfo& hitInformation);

private:

	const float m_maxDistanceTravel = 2000.f;
	float m_distanceTraveled = 0.f;
	float m_aliveTime = 0.f;

	int m_rotationRate = 0;

	static float maxSpeed;

	Collider2D* m_collider = nullptr;

	CollisionComponent* m_collisionComponent = nullptr;
	MovementComponent* m_movementComponent = nullptr;

};