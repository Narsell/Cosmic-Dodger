#include "GameObject.hpp"
#include "CollisionComponent.hpp"
#include "Math.hpp"


GameObject::GameObject()
	:
	m_position(Vector2(0, 0)),
	m_velocity(Vector2(0, 0)),
	m_currentFrame(SDL_Rect({0, 0, 0, 0})),
	m_texture(nullptr)
{
}

GameObject::GameObject(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions)
	:
	m_position(position),
	m_velocity(Vector2(0,0)),
	m_currentFrame(SDL_Rect(0, 0, textureDimensions.x, textureDimensions.y)),
	m_texture(texture)
{

}

GameObject::~GameObject()
{	

}




//void Entity::AddCollider(const Vector2& dimensions, const Vector2& relativePos, const bool renderBounds)
//{
//	m_colliders.emplace_back(
//		new CollisionComponent(dimensions, relativePos, renderBounds)
//	);
//}
//
//const bool Entity::HasCollided(const Entity& otherEntity)
//{
//	for (const CollisionComponent* collider : m_colliders) {
//		for (const CollisionComponent* otherCollider : otherEntity.GetAllColliders()) {
//			if (collider->IsColliding(otherCollider)) {
//				return true;
//			}	
//		}
//	}
//	return false;
//}


