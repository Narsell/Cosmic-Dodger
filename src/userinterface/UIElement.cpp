#include "userinterface/UIElement.hpp"

UIElement::UIElement(const Transform& transform, const char* name)
	:BaseEntity("", name, true, false),
	m_transform(transform),
	m_relativeTransform(transform)
{
}

void UIElement::AddChild(UIElement* child)
{
	m_children.push_back(child);
	child->m_parentElement = this;

	const UIElement* childParent = child->m_parentElement;
	child->m_transform += childParent->m_transform;
	
}

void UIElement::Render(SDL_Renderer* renderer)
{
	BaseEntity::Render(renderer);

	for (UIElement*& uiElement : m_children) {
		if (uiElement->GetCanRender()) {
			uiElement->Render(renderer);
		}
	}
}

void UIElement::Update(const float deltaTime)
{
	BaseEntity::Update(deltaTime);

	for (UIElement*& uiElement : m_children) {
		if (uiElement->GetCanUpdate()) {
			uiElement->Update(deltaTime);
		}
	}
}
