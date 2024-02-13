#include "TextureRect.hpp"
#include "utilities/ResourceManager.hpp"

UITextureRect::UITextureRect(const HUD* parentHud, const TextureResource* texture, const Transform& transform, const char* name)
	:UIElement(parentHud, transform, name),
    m_texture(texture)
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
        m_texture->GetDimensions().x,
        m_texture->GetDimensions().y
    };

    SDL_FPoint center{ dst.w / 2.f, dst.h / 2.f };
    if (m_texture->GetTexture()) {
        SDL_RenderCopyExF(renderer, m_texture->GetTexture(), nullptr, &dst, 90 - m_transform.GetRotation(), &center, SDL_FLIP_NONE);
    }
}
