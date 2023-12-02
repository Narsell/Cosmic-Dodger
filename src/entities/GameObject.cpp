#include "GameObject.hpp"
#include "CollisionComponent.hpp"
#include "Math.hpp"


GameObject::GameObject()
	:
	BaseEntity("", "NA_GameObject", true, true),
	m_position(Vector2(0, 0)),
	m_velocity(Vector2(0, 0)),
	m_currentFrame(SDL_Rect({0, 0, 0, 0})),
	m_texture(nullptr)
{
}

GameObject::GameObject(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions)
	:BaseEntity("", "NA_GameObject", true, true),
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

void GameObject::Render(SDL_Renderer* renderer)
{
    assert(renderer);

    if (!m_isVisible) return;

    SDL_Rect src{
        m_currentFrame.x,
        m_currentFrame.y,
        m_currentFrame.w,
        m_currentFrame.h
    };

    SDL_Rect dst{
        m_position.x,
        m_position.y,
        m_currentFrame.w,
        m_currentFrame.h
    };

    if (m_texture) {
        SDL_RenderCopy(renderer, m_texture, &src, &dst);
    }

    for (Component* component : m_components) {
        component->Render(renderer);
    }
}

void GameObject::Update(const float deltaTime)
{
    if (!m_canUpdate) return;
}
