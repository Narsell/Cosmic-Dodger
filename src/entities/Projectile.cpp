#include "Projectile.hpp"
#include "MovementComponent.hpp"
#include "GameManager.hpp"
#include "Window.hpp"

Projectile::Projectile(const Transform& transform, TextureResource* texture, const char* name)
	:
	GameObject(transform, texture, name)
{
	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(true);
	m_collider = m_collisionComponent->AddCollider(Vector2(9, 9), Vector2::ZERO, false, "Basic Collision");
	std::function<void(HitInfo&)> OnCollisionDelegate = std::bind(&Projectile::OnCollision, this, std::placeholders::_1);
	m_collider->SetCollisionDelegate(OnCollisionDelegate);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetSpeed(1000.f);
	m_movementComponent->SetRotationFollowsVelocity(true);

	m_startPosition = m_transform.GetPosition();

}

Projectile::~Projectile()
{
}

void Projectile::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);
}

void Projectile::OnCollision(HitInfo& hitInformation)
{

	++m_bouncesCounter;
	if (m_bouncesCounter >= m_maxBounces) {
		GameManager::DestroyGameObject(this);
		return;
	}

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
