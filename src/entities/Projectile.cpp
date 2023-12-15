#include "Projectile.hpp"
#include "MovementComponent.hpp"


Projectile::Projectile(const Transform& transform, SDL_Texture* texture, const Vector2& textureDimensions, const char* name)
	:
	GameObject(transform, texture, textureDimensions, name)
{
	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
	m_collisionComponent->SetCanRender(true);

	m_collisionComponent->AddCollider(textureDimensions, Vector2::ZERO, true, "Basic Collision");

	std::function<void(HitInformation&)> OnCollisionDelegate = std::bind(&Projectile::OnCollision, this, std::placeholders::_1);
	m_collisionComponent->SetCollisionDelegate(OnCollisionDelegate);

	m_movementComponent = AddComponent<MovementComponent>(new MovementComponent(this, "Movement Component"));
	m_movementComponent->SetSpeed(5.f);
}

Projectile::~Projectile()
{
	std::cout << GetDisplayName() << " destroyed on Player destructor!\n";
}

void Projectile::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);

}

void Projectile::OnCollision(HitInformation& hitInformation)
{
}
