#include "entities/WindowBounds.hpp"
#include "components/CollisionComponent.hpp"
#include "utilities/ResourceManager.hpp"
#include "Window.hpp"


WindowBounds::WindowBounds(const char* name)
    :GameObject(Transform(), new TextureResource("Window", Vector2::ZERO, nullptr), name)
{

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
    m_collisionComponent->SetCanRender(false);

    const float boundsWidth = 50.f;
    const float windowHeight = static_cast<float>(Window::s_height);
    const float windowWidth = static_cast<float>(Window::s_width);

    m_collisionComponent->AddCollider(Vector2(boundsWidth, windowHeight), Vector2(-boundsWidth/2.f + 10, windowHeight/2.f), true, "LEFT");
    m_collisionComponent->AddCollider(Vector2(boundsWidth, windowHeight), Vector2(windowWidth + boundsWidth / 2.f - 10, windowHeight / 2.f), true, "RIGHT");
    m_collisionComponent->AddCollider(Vector2(windowWidth, boundsWidth), Vector2(windowWidth/2.f, -boundsWidth / 2.f + 10), true, "UP");
    m_collisionComponent->AddCollider(Vector2(windowWidth, boundsWidth), Vector2(windowWidth / 2.f, windowHeight  + boundsWidth / 2.f - 10), true, "DOWN");
}

