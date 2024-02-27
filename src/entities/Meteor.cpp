#include "entities/Meteor.hpp"
#include "entities/Player.hpp"
#include "components/MovementComponent.hpp"
#include "components/CollisionComponent.hpp"
#include "components/AnimationComponent.hpp"
#include "utilities/ResourceManager.hpp"
#include "utilities/MeteorSpawner.hpp"
#include "utilities/GameState.hpp"
#include "GameManager.hpp"

float Meteor::maxSpeed = 350.f;

Meteor::Meteor(const Transform& transform, const Vector2& initialVelocity, const float speed, const char* name)
	:GameObject(transform, ResourceManager::meteorTexture, name)
{
	while (m_rotationRate == 0) {
		m_rotationRate = Math::RandomRange(-2, 2);
	}
	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetVelocity(initialVelocity);
	m_movementComponent->SetMaxSpeed(maxSpeed);
	m_movementComponent->SetSpeed(speed);

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(false);
	m_collider = m_collisionComponent->AddCollider(ResourceManager::meteorTexture->GetDimensions() * 0.7f, Vector2::ZERO, true, "Meteor Collision");
	std::function<void(HitInfo&)> OnCollisionDelegate = std::bind(&Meteor::OnCollision, this, std::placeholders::_1);
	m_collider->SetCollisionDelegate(OnCollisionDelegate);
	m_collider->ListenForCollisions(GameManager::GetPlayer());

	m_animationComponent = AddComponent<AnimationComponent>(new AnimationComponent(this, "Animation Component"));
	Animation* destroyAnimation = m_animationComponent->AddAnimation(new Animation("Destroy", ResourceManager::meteorDestroyFrames, 12));
	destroyAnimation->SetTimeoutDelegate(std::bind(&Meteor::OnDestroyAnimationFinish, this));

}

Meteor::~Meteor()
{
}

void Meteor::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

	m_aliveTime += deltaTime;

	m_distanceTraveled = m_movementComponent->GetSpeed() * m_aliveTime;

	if (m_distanceTraveled > m_maxDistanceTravel) {
		MeteorSpawner::DeleteMeteor(this);
	}

	m_transform.SetRotation(m_transform.GetRotation() + m_rotationRate);
}

void Meteor::OnCollision(HitInfo& hitInformation)
{
	m_collider->Disable();
	m_animationComponent->PlayAnimation("Destroy");
	m_rotationRate = 0;
	m_movementComponent->SetMaxSpeed(m_movementComponent->GetSpeed() * 0.1f);

	if (hitInformation.hitGameObject->GetDisplayName() == "Player") {
		GameState::GetGameState()->OnPlayerHit();
	}
}

void Meteor::OnDestroyAnimationFinish()
{
	MeteorSpawner::DeleteMeteor(this);
}
