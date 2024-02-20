#include "SDL.h"
#include <iostream>

#include "entities/GameObject.hpp"
#include "components/Component.hpp"
#include "utilities/Math.hpp"
#include "utilities/ResourceManager.hpp"


GameObject::GameObject()
	:
	BaseEntity("", "NA_GameObject", true, true),
    m_transform(Transform()),
	m_textureResource(nullptr)
{
}

GameObject::GameObject(const Transform& transform, TextureResource* texture, const char* name)
	:BaseEntity("", name, true, true),
    m_transform(transform),
	m_textureResource(texture),
    m_centerPoint(texture->GetDimensions() / 2.f)
{
}

GameObject::~GameObject()
{
    //std::cout << GetDisplayName() << " destroyed on GameObject destructor!\n";

	for (Component*& component : m_components) {
		delete component;
	}
}

void GameObject::Render(SDL_Renderer* renderer)
{
    BaseEntity::Render(renderer);

    SDL_FRect dst {
        m_transform.GetPosition().x,
        m_transform.GetPosition().y,
        m_textureResource->GetDimensions().x,
        m_textureResource->GetDimensions().y
    };

    SDL_FPoint center{ m_textureResource->GetDimensions().x / 2.f,  m_textureResource->GetDimensions().y / 2.f };

    if (m_textureResource->GetTexture()) {
        SDL_RenderCopyExF(renderer, m_textureResource->GetTexture(), nullptr, &dst, 90 - m_transform.GetRotation(), &center, SDL_FLIP_NONE);
        
        ////Draw rotation center point
        //float absoluteCenter_x = m_transform.GetPosition().x + center.x;
        //float absoluteCenter_y = m_transform.GetPosition().y + center.y;
        //SDL_RenderDrawLineF(renderer, absoluteCenter_x - 5, absoluteCenter_y, absoluteCenter_x + 5, absoluteCenter_y);
        //SDL_RenderDrawLineF(renderer, absoluteCenter_x, absoluteCenter_y - 5, absoluteCenter_x, absoluteCenter_y + 5);
    
    }

    for (Component*& component : m_components) {
        if (component->GetCanRender()) {
            component->Render(renderer);
        }
    }
}

void GameObject::Update(const float deltaTime)
{
    BaseEntity::Update(deltaTime);

    for (Component*& component : m_components) {
        if (component->GetCanUpdate()) {
            component->Update(deltaTime);
        }
    }
}

void GameObject::Disable()
{
    BaseEntity::Disable();
    for (Component*& component : m_components) {
        component->SetCanUpdate(false);
        component->SetCanRender(false);
    }
}
