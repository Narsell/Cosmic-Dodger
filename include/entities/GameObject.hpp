#pragma once
#include <SDL.h>
#include <vector>
#include <assert.h>

#include "Math.hpp"
#include "BaseEntity.hpp"
#include "Transform.hpp"

struct TextureResource;
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

	//Makes an object unable to update and render, as well as its child components.
	void Disable();

	const SDL_FRect& GetCurrentFrame() const { return m_currentFrame; };

	template<typename ComponentType>
	inline ComponentType* AddComponent(ComponentType* component);

	template<typename ComponentType>
	inline ComponentType* GetComponentOfType();

protected:

	GameObject(const Transform& transform, TextureResource* texture, const char* name = "NA_GameObject");
	GameObject();

private:

	SDL_FRect m_currentFrame;
	TextureResource* m_texture = nullptr;
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
