#include "WindowBounds.hpp"
#include "CollisionComponent.hpp"


WindowBounds::WindowBounds(const Vector2& windowDimensions, const char* name)
    :GameObject(Transform(), nullptr, Vector2::ZERO, name)
{

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
    m_collisionComponent->SetCanRender(true);

    int boundsWidth = 1;

    m_collisionComponent->AddCollider(Vector2(boundsWidth, windowDimensions.y), Vector2(0, 0), true, "LEFT");
    m_collisionComponent->AddCollider(Vector2(boundsWidth, windowDimensions.y), Vector2(windowDimensions.x - boundsWidth, 0), true, "RIGHT");
    m_collisionComponent->AddCollider(Vector2(windowDimensions.x, boundsWidth), Vector2(0, 0), true, "UP");
    m_collisionComponent->AddCollider(Vector2(windowDimensions.x, boundsWidth), Vector2(0, windowDimensions.y - boundsWidth), true, "DOWN");
}

