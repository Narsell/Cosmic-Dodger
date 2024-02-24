#include "userinterface/UIElement.hpp"

void UIElement::Construct()
{
	for (UIElement*& child : m_children) 
	{
		child->m_transform += this->m_transform;
		child->Construct();
	}
}

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
