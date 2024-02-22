#include "userinterface/UITextureRect.hpp"
#include "utilities/ResourceManager.hpp"

UITextureRect::UITextureRect(const TextureResource& texture, const Transform& transform, const char* name)
	:UIElement(transform, name),
    m_textureResource(texture)
{
    m_transform.SetRotation(90);
}

UITextureRect::~UITextureRect()
{
}

void UITextureRect::Render(SDL_Renderer* renderer)
{
    SDL_FRect dst{
        m_transform.GetPosition().x,
        m_transform.GetPosition().y,
        m_textureResource.GetDimensions().x,
        m_textureResource.GetDimensions().y
    };

    SDL_FPoint center{ dst.w / 2.f, dst.h / 2.f };
    if (m_textureResource.GetTexture()) {
        SDL_RenderCopyExF(renderer, m_textureResource.GetTexture(), nullptr, &dst, 90 - m_transform.GetRotation(), &center, SDL_FLIP_NONE);
    }

    UIElement::Render(renderer);
}
