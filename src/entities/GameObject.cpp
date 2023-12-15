#include <iostream>

#include "GameObject.hpp"
#include "CollisionComponent.hpp"
#include "Math.hpp"


GameObject::GameObject()
	:
	BaseEntity("", "NA_GameObject", true, true),
	m_currentFrame(SDL_Rect({0, 0, 0, 0})),
	m_texture(nullptr)
{
}

GameObject::GameObject(const Transform& transform, SDL_Texture* texture, const Vector2& textureDimensions, const char* name)
	:BaseEntity("", name, true, true),
    m_transform(transform),
	m_currentFrame(SDL_Rect(0, 0, textureDimensions.x, textureDimensions.y)),
	m_texture(texture)
{
}

GameObject::~GameObject()
{
    std::cout << GetDisplayName() << " destroyed on GameObject destructor!\n";

	for (Component* component : m_components) {
		delete component;
	}
}

void GameObject::Render(SDL_Renderer* renderer)
{
    BaseEntity::Render(renderer);

    SDL_Rect src {
        m_currentFrame.x,
        m_currentFrame.y,
        m_currentFrame.w,
        m_currentFrame.h
    };

    SDL_Rect dst {
        m_transform.GetPosition().x,
        m_transform.GetPosition().y,
        m_currentFrame.w,
        m_currentFrame.h
    };

    SDL_Point center{ m_currentFrame.w / 2, m_currentFrame.w / 2 };

    if (m_texture) {
        //SDL_RenderCopy(renderer, m_texture, &src, &dst);
        SDL_RenderCopyEx(renderer, m_texture, &src, &dst, m_transform.GetRotation(), &center, SDL_FLIP_NONE);
    }

    for (Component* component : m_components) {
        if (component->GetCanRender()) {
            component->Render(renderer);
        }
    }
}

void GameObject::Update(const float deltaTime)
{
    BaseEntity::Update(deltaTime);

    for (Component* component : m_components) {
        if (component->GetCanUpdate()) {
            component->Update(deltaTime);
        }
    }
}
