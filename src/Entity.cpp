#include "Entity.hpp"
#include "Collider2D.hpp"

Entity::Entity(const Vector2& position, SDL_Texture* texture)
	:
	m_position(position),
	m_currentFrame(SDL_Rect(0, 0, 32, 32)),
	m_texture(texture),
	m_collider(new Collider2D(SDL_Rect({0, 0, 32, 32}), Vector2(5.f), true))
{

}

Entity::~Entity()
{	
	if (m_texture) {
		SDL_DestroyTexture(m_texture);
	}
	if (m_collider) {
		delete m_collider;
	}
}

void Entity::Update()
{
	m_collider->Update(this);
}

void Entity::AddPositionDelta(const Vector2& deltaPosition)
{
	m_position += deltaPosition;
}

