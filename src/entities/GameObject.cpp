#include "GameObject.hpp"
#include "CollisionComponent.hpp"
#include "Math.hpp"


GameObject::GameObject()
	:
	BaseEntity("", "NA_GameObject"),
	m_position(Vector2(0, 0)),
	m_velocity(Vector2(0, 0)),
	m_currentFrame(SDL_Rect({0, 0, 0, 0})),
	m_texture(nullptr)
{
}

GameObject::GameObject(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions)
	:BaseEntity("", "NA_GameObject"),
	m_position(position),
	m_velocity(Vector2(0,0)),
	m_currentFrame(SDL_Rect(0, 0, textureDimensions.x, textureDimensions.y)),
	m_texture(texture)
{

}

GameObject::~GameObject()
{	
	//Note: GameObject doesn't have ownership of m_texture, no need to delete it

	for (Component* component : m_components) {
		delete component;
	}
}
