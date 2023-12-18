#include "Projectile.hpp"
#include "MovementComponent.hpp"
#include "GameManager.hpp"
#include "Renderer.hpp"

Projectile::Projectile(const Transform& transform, TextureResource* texture, const char* name)
	:
	GameObject(transform, texture, name)
{
	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(true);

	m_collisionComponent->AddCollider(texture->GetDimensions(), Vector2::ZERO, true, "Basic Collision");

	std::function<void(HitInformation&)> OnCollisionDelegate = std::bind(&Projectile::OnCollision, this, std::placeholders::_1);
	m_collisionComponent->SetCollisionDelegate(OnCollisionDelegate);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetSpeed(5.f);
}

Projectile::~Projectile()
{
	//std::cout << GetDisplayName() << " destroyed on Player destructor!\n";
}

void Projectile::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

}

void Projectile::OnCollision(HitInformation& hitInformation)
{
	//std::cout << "Projectile Collision!\n";
	if (hitInformation.hitGameObject->GetDisplayName() == "Window Bounds") {
		if (hitInformation.hitCollider->GetDisplayName() == "UP" ||
			hitInformation.hitCollider->GetDisplayName() == "DOWN") {

			/*
				TODO: Rework it like this
				Have a velocity vector (in MovementComponent) which points to the direction of movement (RIGHT by default)
				Have rotation angle/vector which simply controls texture rotation
				Then have rotationFollowsVelocity variable to make object rotate towards direction of movement every tick.
			*/

		}
		else if (hitInformation.hitCollider->GetDisplayName() == "RIGHT" ||
				 hitInformation.hitCollider->GetDisplayName() == "LEFT") {

		}

	}
}
