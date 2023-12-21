#include "WindowBounds.hpp"
#include "CollisionComponent.hpp"
#include "Renderer.hpp"


WindowBounds::WindowBounds(const Vector2& windowDimensions, const char* name)
    :GameObject(Transform(), new TextureResource("Window", Vector2::ZERO, nullptr), name)
{

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
    m_collisionComponent->SetCanRender(false);

    const float boundsWidth = 1.f;

    m_collisionComponent->AddCollider(Vector2(boundsWidth, windowDimensions.y), Vector2(0, 0), true, "LEFT");
    m_collisionComponent->AddCollider(Vector2(boundsWidth, windowDimensions.y), Vector2(windowDimensions.x - boundsWidth, 0), true, "RIGHT");
    m_collisionComponent->AddCollider(Vector2(windowDimensions.x, boundsWidth), Vector2(0, 0), true, "UP");
    m_collisionComponent->AddCollider(Vector2(windowDimensions.x, boundsWidth), Vector2(0, windowDimensions.y - boundsWidth), true, "DOWN");
}

