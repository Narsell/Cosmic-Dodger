#pragma once
#include <vector>
#include <assert.h>

#include "utilities/Math.hpp"
#include "entities/BaseEntity.hpp"
#include "components/Transform.hpp"

struct TextureResource;
class Component;

class GameObject : public BaseEntity
{
public:

	~GameObject() override;

	Transform m_transform;

	const Vector2 GetCenterPoint() const { return m_centerPoint; };
	void SetTextureResource(const TextureResource* textureResource) { m_textureResource = textureResource; };

	const TextureResource* GetTextureResource() const { return m_textureResource; };
	
	//Renders the game object texture and its components
	virtual void Render(SDL_Renderer* renderer) override;

	//Updates and "physics"
	virtual void Update(const float deltaTime) override;

	//Makes an object unable to update and render, as well as its child components.
	void Disable() override;

	template<typename ComponentType>
	inline ComponentType* AddComponent(ComponentType* component);

	template<typename ComponentType>
	inline ComponentType* GetComponentOfType() const;

protected:

	GameObject(const Transform& transform, TextureResource* texture, const char* name = "NA_GameObject");
	GameObject();

private:

	const TextureResource* m_textureResource = nullptr;
	Vector2 m_centerPoint;
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
ComponentType* GameObject::GetComponentOfType() const {
	ComponentType* result = nullptr;
	for (Component* component : m_components)
	{
		result = dynamic_cast<ComponentType*>(component);
		if (result)
			break;
	}
	return result;
}
