#include "WindowBounds.hpp"
#include "CollisionComponent.hpp"
#include "Window.hpp"


WindowBounds::WindowBounds(const char* name)
    :GameObject(Transform(), new TextureResource("Window", Vector2::ZERO, nullptr), name)
{

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
    m_collisionComponent->SetCanRender(false);

    const float boundsWidth = 1.f;

    const float windowHeight = static_cast<float>(Window::s_height);
    const float windowWidth = static_cast<float>(Window::s_width);

    m_collisionComponent->AddCollider(Vector2(boundsWidth, windowHeight), Vector2(0, 0), true, "LEFT");
    m_collisionComponent->AddCollider(Vector2(boundsWidth, windowHeight), Vector2(windowWidth - boundsWidth, 0), true, "RIGHT");
    m_collisionComponent->AddCollider(Vector2(windowWidth, boundsWidth), Vector2(0, 0), true, "UP");
    m_collisionComponent->AddCollider(Vector2(windowWidth, boundsWidth), Vector2(0, windowHeight - boundsWidth), true, "DOWN");
}

