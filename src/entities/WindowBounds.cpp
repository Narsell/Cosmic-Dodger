#include "WindowBounds.hpp"
#include "CollisionComponent.hpp"


WindowBounds::WindowBounds(const Vector2& windowDimensions, const char* name)
    :GameObject(Vector2::ZERO, nullptr, Vector2::ZERO, name)
{

	m_collisionComponent = AddComponent<CollisionComponent>(new CollisionComponent(this, "Collision Component"));
    m_collisionComponent->SetCanRender(true);

    m_collisionComponent->AddCollider(Vector2(10, windowDimensions.y), Vector2(0, 0), true, "LEFT");
    m_collisionComponent->AddCollider(Vector2(10, windowDimensions.y), Vector2(windowDimensions.x - 10, 0), true, "RIGHT");
    m_collisionComponent->AddCollider(Vector2(windowDimensions.x, 10), Vector2(0, 0), true, "UP");
    m_collisionComponent->AddCollider(Vector2(windowDimensions.x, 10), Vector2(0, windowDimensions.y - 10), true, "DOWN");
}

