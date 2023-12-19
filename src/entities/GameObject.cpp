#include <iostream>

#include "GameObject.hpp"
#include "CollisionComponent.hpp"
#include "Math.hpp"
#include "Renderer.hpp"


GameObject::GameObject()
	:
	BaseEntity("", "NA_GameObject", true, true),
    m_transform(Transform()),
	m_currentFrame(SDL_Rect({0, 0, 0, 0})),
	m_texture(nullptr)
{
}

GameObject::GameObject(const Transform& transform, TextureResource* texture, const char* name)
	:BaseEntity("", name, true, true),
    m_transform(transform),
	m_currentFrame(SDL_Rect(0, 0, texture->GetDimensions().x, texture->GetDimensions().y)),
	m_texture(texture)
{
}

GameObject::~GameObject()
{
    //std::cout << GetDisplayName() << " destroyed on GameObject destructor!\n";

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

    SDL_Point center{ m_currentFrame.w / 2, m_currentFrame.h / 2 };

    if (m_texture->GetTexture()) {
        SDL_RenderCopyEx(renderer, m_texture->GetTexture(), &src, &dst, 90 - m_transform.GetRotation(), &center, SDL_FLIP_NONE);
        float absoluteCenter_x = m_transform.GetPosition().x + center.x;
        float absoluteCenter_y = m_transform.GetPosition().y + center.y;
        SDL_RenderDrawLineF(renderer, absoluteCenter_x - 5, absoluteCenter_y, absoluteCenter_x + 5, absoluteCenter_y);
        SDL_RenderDrawLineF(renderer, absoluteCenter_x, absoluteCenter_y - 5, absoluteCenter_x, absoluteCenter_y + 5);
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
