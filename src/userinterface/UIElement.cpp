#include "userinterface/UIElement.hpp"

UIElement::UIElement(const Transform& transform, const char* name)
	:BaseEntity("", name, true, false),
	m_transform(transform)
{
}

void UIElement::AddChild(UIElement* child)
{
	m_children.push_back(child);
	child->m_parentElement = this;
	child->m_transform += m_transform;
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
