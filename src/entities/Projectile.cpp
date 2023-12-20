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

	m_collisionComponent->AddCollider(Vector2(9, 9), Vector2::ZERO, false, "Basic Collision");

	std::function<void(HitInformation&)> OnCollisionDelegate = std::bind(&Projectile::OnCollision, this, std::placeholders::_1);
	m_collisionComponent->SetCollisionDelegate(OnCollisionDelegate);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetSpeed(5.f);
	m_movementComponent->SetRotationFollowsVelocity(true);
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
	if (hitInformation.hitGameObject->GetDisplayName() == "Window Bounds") {

		const Vector2 currentVelocity = m_movementComponent->GetVelocity();

		if (hitInformation.hitCollider->GetDisplayName() == "UP" || hitInformation.hitCollider->GetDisplayName() == "DOWN") {
			const Vector2 newVelocity = Vector2(currentVelocity.x, -currentVelocity.y);
			m_movementComponent->SetVelocity(newVelocity);
		}
		else if (hitInformation.hitCollider->GetDisplayName() == "RIGHT" || hitInformation.hitCollider->GetDisplayName() == "LEFT") {

			const Vector2 newVelocity = Vector2(-currentVelocity.x, currentVelocity.y);
			m_movementComponent->SetVelocity(newVelocity);
		}
	}

}
