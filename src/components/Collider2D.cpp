#include <SDL.h>
#include <assert.h>
#include <cmath>

#include "components/Collider2D.hpp"
#include "entities/GameObject.hpp"
#include "components/CollisionComponent.hpp"


Collider2D::Collider2D(const Vector2& dimensions, CollisionComponent* parentComp, const Vector2& relativePos, const bool visible, const char* name)
	:
	BaseEntity("", name, visible, true),
	m_absTransform(Transform()),
	m_relTransform(relativePos, 0.f, 1.f),
	m_colliderRectangle({ 0, 0, dimensions.x, dimensions.y }),
	m_parentComponent(parentComp)
{
}

Collider2D::~Collider2D()
{
	//std::cout << GetDisplayName() << " destroyed on Collider destructor!\n";

}

void Collider2D::Render(SDL_Renderer* renderer)
{
	BaseEntity::Render(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRectF(renderer, &m_colliderRectangle);
}

void Collider2D::Update(const float deltaTime)
{
	BaseEntity::Update(deltaTime);

	m_absTransform = m_parentComponent->m_transform;

	m_colliderRectangle.x = m_absTransform.GetPosition().x + m_relTransform.GetPosition().x;
	m_colliderRectangle.y = m_absTransform.GetPosition().y + m_relTransform.GetPosition().y;

	for (Collider2D* collisionCandidate : m_collisionCandidates) {
		const bool isColliding = IsColliding(collisionCandidate, m_lastHitInformation);
		if (isColliding && GetCanUpdate() && OnCollisionDelegate) {
			OnCollisionDelegate(m_lastHitInformation);
		}
		else if(isColliding && (!GetCanUpdate() || !OnCollisionDelegate)) {
			std::cout << "[WARNING] Unable to call collision delegate\n";
		}
	}
}

void Collider2D::ListenForCollisions(Collider2D* collisionCandidate)
{
	assert(collisionCandidate);
	m_collisionCandidates.emplace_back(collisionCandidate);
}

void Collider2D::ListenForCollisions(std::vector<Collider2D*> newCollisionCandidates)
{
	m_collisionCandidates.reserve(m_collisionCandidates.size() + newCollisionCandidates.size());
	m_collisionCandidates.insert(m_collisionCandidates.end(), newCollisionCandidates.begin(), newCollisionCandidates.end());
}

void Collider2D::SetCollisionDelegate(std::function<void(HitInfo&)> delegate)
{
	OnCollisionDelegate = delegate;
}

bool Collider2D::IsColliding(Collider2D* other, HitInfo& OutHitInformation) const
{
	assert(other);

	if (SDL_HasIntersectionF(&m_colliderRectangle, &other->m_colliderRectangle)) {

		CollisionComponent* parentCollisionComp = other->m_parentComponent;
		assert(parentCollisionComp);

		OutHitInformation.hasHit = true;
		OutHitInformation.hitLocation = m_parentComponent->m_transform.GetPosition();
		OutHitInformation.hitCollider = other;
		OutHitInformation.hitGameObject = parentCollisionComp->GetParent();

		return true;
	}
	return false;
}

void HitInfo::Print() const
{
	std::cout << "HitInfo:\n"
		"\tCollision: " << hasHit << "\n"
		"\tLocation: (" << hitLocation.x << "," << hitLocation.y << ")\n"
		"\tCollider: " << hitCollider->GetDisplayName() << "\n"
		"\tObject: " << hitGameObject->GetDisplayName() << "\n"
		<< "===========================================\n";
}
