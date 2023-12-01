#pragma once
#include <SDL.h>
#include <vector>
#include <assert.h>

#include "Math.hpp"
#include "BaseEntity.hpp"

class Component;

class GameObject : public BaseEntity
{
public:
	GameObject(const GameObject& copy) = delete;
	const GameObject& operator=(const GameObject& other) = delete;
	virtual ~GameObject();

	template<typename ComponentType>
	inline ComponentType* AddComponent(ComponentType* component);

	template<typename ComponentType>
	inline ComponentType* GetComponentOfType();
	
	//Updates and "physics"
	void Update(const float deltaTime) override {};

	// Getters
	const Vector2& GetPosition() const { return m_position; };
	const Vector2& GetVelocity() const { return m_velocity; };
	SDL_Texture* GetTexture() const { return m_texture; };
	SDL_Rect GetCurrentFrame() const { return m_currentFrame; };

protected:
	GameObject(const Vector2& position, SDL_Texture* texture, const Vector2& textureDimensions);
	GameObject();

	Vector2 m_position;
	Vector2 m_velocity;
	SDL_Rect m_currentFrame;
	SDL_Texture* m_texture = nullptr;
	//Has ownership of all components on child classes. This class will take care of freeing memory on all components
	std::vector<Component*> m_components;
};


template<typename ComponentType>
ComponentType* GameObject::AddComponent(ComponentType* component)
{
	assert(component);
	m_components.emplace_back(component);
	return component;
}

template<typename ComponentType>
ComponentType* GameObject::GetComponentOfType() {
	ComponentType* result = nullptr;
	for (Component* component : m_components)
	{
		result = dynamic_cast<ComponentType*>(component);
		if (result)
			break;
	}
	return result;
}
