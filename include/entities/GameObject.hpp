#pragma once
#include <SDL.h>
#include <vector>
#include <assert.h>

#include "Math.hpp"
#include "BaseEntity.hpp"
#include "Transform.hpp"

class Component;

class GameObject : public BaseEntity
{
public:
	GameObject(const GameObject& copy) = delete;
	const GameObject& operator=(const GameObject& other) = delete;
	~GameObject() override;

	Transform m_transform;
	
	//Renders the game object texture and its components
	virtual void Render(SDL_Renderer* renderer) override;

	//Updates and "physics"
	virtual void Update(const float deltaTime) override;

	SDL_Texture* GetTexture() const { return m_texture; };
	SDL_Rect GetCurrentFrame() const { return m_currentFrame; };

	template<typename ComponentType>
	inline ComponentType* AddComponent(ComponentType* component);

	template<typename ComponentType>
	inline ComponentType* GetComponentOfType();

protected:

	GameObject(const Transform& transform, SDL_Texture* texture, const Vector2& textureDimensions, const char* name = "NA_GameObject");
	GameObject();

private:

	SDL_Rect m_currentFrame;
	SDL_Texture* m_texture = nullptr;
	//Has ownership of all components. This class will take care of freeing memory on all components
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
