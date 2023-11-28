#include "Entity.hpp"
#include "Collider2D.hpp"

Entity::Entity(const Vector2& position, SDL_Texture* texture)
	:
	m_position(position),
	m_velocity(Vector2(0,0)),
	m_currentFrame(SDL_Rect(0, 0, 32, 32)),
	m_texture(texture)
{

}

Entity::~Entity()
{	
	for (Collider2D* collider : m_colliders) {
		delete collider;
	}
	// Not ideal, should use shared_ptr
	if (m_texture) {
		SDL_DestroyTexture(m_texture);
	}

}

void Entity::Update()
{
	AddPositionDelta(m_velocity);
	for (Collider2D* collider : m_colliders) {
		collider->Update(this);
	}
}

void Entity::AddPositionDelta(const Vector2& deltaPosition)
{
	m_position += deltaPosition;
}

void Entity::AddCollider(const Vector2& dimensions, const Vector2& relativePos, const bool renderBounds)
{
	m_colliders.emplace_back(
		new Collider2D(dimensions, relativePos, renderBounds)
	);
}

const bool Entity::HasCollided(const Entity& otherEntity)
{
	for (const Collider2D* collider : m_colliders) {
		for (const Collider2D* otherCollider : otherEntity.GetAllColliders()) {
			if (collider->IsColliding(*otherCollider)) {
				return true;
			}	
		}
	}
	return false;
}

