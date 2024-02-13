#include <algorithm>

#include "userinterface/PlayerLives.hpp"
#include "utilities/ResourceManager.hpp"
#include "Window.hpp"

UIPlayerLives::UIPlayerLives(const HUD* parentHud, const Transform& transform, const int maxLives, const char* name)
	:UIElement(parentHud, transform, name),
	m_maxLives(maxLives),
	m_currentLives(m_maxLives)
{
	m_lives.reserve(m_maxLives);
	for (int i = 0; i < m_maxLives; ++i) {
		const float xOffset = i * (ResourceManager::playerLifeTexture->GetDimensions().x + m_paddingRight) + m_transform.GetPosition().x;
		const float yOffset = m_transform.GetPosition().y;
		m_lives.emplace_back(
			new UITextureRect(parentHud, ResourceManager::playerLifeTexture, Transform(Vector2(xOffset, yOffset)))
		);
	}

}

void UIPlayerLives::UpdateCurrentLives(const int currentLives)
{
	m_currentLives = currentLives;
}

void UIPlayerLives::Render(SDL_Renderer* renderer)
{
	int livesRendered = 0;
	for (std::vector<UITextureRect*>::reverse_iterator i = m_lives.rbegin(); i != m_lives.rend(); ++i) {
		if (livesRendered == m_currentLives) {
			break;
		}
		UITextureRect* lifeElement = *i;
		if (lifeElement->GetCanRender()) {
			lifeElement->Render(renderer);
		}
		++livesRendered;
	}
}
