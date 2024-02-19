#include "userinterface/UIProgressTextures.hpp"
#include "utilities/ResourceManager.hpp"

UIProgressTextures::UIProgressTextures(const HUD* parentHud, const Transform& transform, TextureResource* texture, const int maxValue, const char* name)
	:UIElement(parentHud, transform, name),
	m_maxValue(maxValue),
	m_currentValue(m_maxValue),
	m_textureResource(texture)
{
	assert(m_textureResource);
	m_textures.reserve(m_maxValue);
	for (int i = 0; i < m_maxValue; ++i) {
		//TODO: Get grow direction logic here
		const float xOffset = m_transform.GetPosition().x - i * (m_textureResource->GetDimensions().x + m_padding);
		const float yOffset = m_transform.GetPosition().y;
		m_textures.emplace_back(
			new UITextureRect(parentHud, m_textureResource, Transform(Vector2(xOffset, yOffset)))
		);
	}
}

UIProgressTextures::~UIProgressTextures()
{
	for (UITextureRect* texture : m_textures) {
		delete texture;
	}
}

void UIProgressTextures::UpdateValue(const int currentValue)
{
	m_currentValue = currentValue;
}

void UIProgressTextures::Render(SDL_Renderer* renderer)
{
	int texturesRendered = 0;
	for (std::vector<UITextureRect*>::iterator i = m_textures.begin(); i != m_textures.end(); ++i) {
		if (texturesRendered == m_currentValue) {
			break;
		}
		UITextureRect* lifeElement = *i;
		if (lifeElement->GetCanRender()) {
			lifeElement->Render(renderer);
		}
		++texturesRendered;
	}
}
