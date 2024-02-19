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
	m_collisionCandidates.clear();
}

void Collider2D::Render(SDL_Renderer* renderer)
{
	BaseEntity::Render(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);

	SDL_RenderDrawRectF(renderer, &m_colliderRectangle);
}

void Collider2D::Update(const float deltaTime)
{
	BaseEntity::Update(deltaTime);

	Transform parentTransform = m_parentComponent->m_transform;

	m_absTransform.SetRotation(parentTransform.GetRotation());
	m_absTransform.SetScale(parentTransform.GetScale());

	const Vector2 absoluteCenter = parentTransform.GetPosition() + m_parentComponent->GetParent()->GetCenterPoint();
	const float rotation = Math::DegreesToRadians(parentTransform.GetRotation());
	const Vector2 relativePosition = m_relTransform.GetPosition().RotatedBy(rotation);
	const Vector2 absolutePosition = Vector2(
		absoluteCenter.x + relativePosition.x - m_colliderRectangle.w / 2.f,
		absoluteCenter.y + relativePosition.y - m_colliderRectangle.h / 2.f
	);

	m_absTransform.SetPosition(absolutePosition);

	m_colliderRectangle.x = m_absTransform.GetPosition().x;
	m_colliderRectangle.y = m_absTransform.GetPosition().y;
	
	for (Collider2D* collisionCandidate : m_collisionCandidates) {
		const bool isColliding = IsColliding(collisionCandidate, m_lastHitInformation);
		if (isColliding && GetCanUpdate() && collisionCandidate->GetCanUpdate() && OnCollisionDelegate)
		{
			OnCollisionDelegate(m_lastHitInformation);
		}
		else if(isColliding && (!GetCanUpdate() || collisionCandidate->GetCanUpdate() || !OnCollisionDelegate))
		{
			std::cout << "[WARNING] Unable to call collision delegate\n";
		}
	}
}

void Collider2D::ListenForCollisions(Collider2D* collisionCandidate)
{
	assert(collisionCandidate);
	m_collisionCandidates.emplace_back(collisionCandidate);
}

void Collider2D::ListenForCollisions(const GameObject* collisionCandidate)
{
	CollisionComponent* collisionComp = collisionCandidate->GetComponentOfType<CollisionComponent>();
	if (collisionComp) {
		ListenForCollisions(collisionComp->GetAllColliders());
	}
}

void Collider2D::ListenForCollisions(const std::vector<Collider2D*> newCollisionCandidates)
{
	std::copy(newCollisionCandidates.begin(), newCollisionCandidates.end(), std::back_inserter(m_collisionCandidates));
}

void Collider2D::SetCollisionDelegate(std::function<void(HitInfo&)> delegate)
{
	OnCollisionDelegate = delegate;
}

const bool Collider2D::IsColliding(Collider2D* other, HitInfo& OutHitInformation) const
{
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
	std::cout << std::boolalpha;
	std::cout << "HitInfo:\n"
		"\tCollision: " << hasHit << "\n"
		"\tLocation: (" << hitLocation.x << "," << hitLocation.y << ")\n"
		"\tCollider: " << hitCollider->GetDisplayName() << "\n"
		"\tObject: " << hitGameObject->GetDisplayName() << "\n"
		<< "===========================================\n";
	std::cout << std::boolalpha;
}
