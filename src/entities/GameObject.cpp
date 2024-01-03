#include <iostream>

#include "GameObject.hpp"
#include "CollisionComponent.hpp"
#include "Math.hpp"
#include "Window.hpp"


GameObject::GameObject()
	:
	BaseEntity("", "NA_GameObject", true, true),
    m_transform(Transform()),
	m_currentFrame(SDL_FRect(0.f, 0.f, 0.f, 0.f)),
	m_texture(nullptr)
{
}

GameObject::GameObject(const Transform& transform, TextureResource* texture, const char* name)
	:BaseEntity("", name, true, true),
    m_transform(transform),
	m_currentFrame(SDL_FRect(0.f, 0.f, texture->GetDimensions().x, texture->GetDimensions().y)),
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
        static_cast<int>(m_currentFrame.x),
        static_cast<int>(m_currentFrame.y),
        static_cast<int>(m_currentFrame.w),
        static_cast<int>(m_currentFrame.h)
    };

    SDL_FRect dst {
        m_transform.GetPosition().x,
        m_transform.GetPosition().y,
        m_currentFrame.w,
        m_currentFrame.h
    };

    SDL_FPoint center{ m_currentFrame.w / 2.f, m_currentFrame.h / 2.f };

    if (m_texture->GetTexture()) {
        SDL_RenderCopyExF(renderer, m_texture->GetTexture(), &src, &dst, 90 - m_transform.GetRotation(), &center, SDL_FLIP_NONE);
        
        ////Draw rotation center point
        //float absoluteCenter_x = m_transform.GetPosition().x + center.x;
        //float absoluteCenter_y = m_transform.GetPosition().y + center.y;
        //SDL_RenderDrawLineF(renderer, absoluteCenter_x - 5, absoluteCenter_y, absoluteCenter_x + 5, absoluteCenter_y);
        //SDL_RenderDrawLineF(renderer, absoluteCenter_x, absoluteCenter_y - 5, absoluteCenter_x, absoluteCenter_y + 5);
    
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

void GameObject::Disable()
{
    SetCanUpdate(false);
    SetCanRender(false);
    for (Component* component : m_components) {
        component->SetCanUpdate(false);
        component->SetCanRender(false);
    }
}
