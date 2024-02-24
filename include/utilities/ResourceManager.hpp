#pragma once
#include <assert.h>
#include <vector>
#include <map>
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "utilities/Math.hpp"


struct TextureResource {

public:

    TextureResource(const char* name, const Vector2& dimensions, SDL_Texture* texture);
    TextureResource(const TextureResource&) = delete;
    const TextureResource& operator=(const TextureResource&) = delete;
    ~TextureResource();

    const char* GetName() const { return m_name; };
    const Vector2& GetDimensions() const { return m_dimensions; };
    SDL_Texture* GetTexture() const { return m_texture; };

private:
    const char* m_name;
    const Vector2 m_dimensions;
    SDL_Texture* m_texture;
};

class AnimationFrames {

public:
    AnimationFrames(const char* name);
    AnimationFrames(const AnimationFrames&) = delete;
    const AnimationFrames& operator=(const AnimationFrames&) = delete;
    ~AnimationFrames() {};

    const std::vector<const TextureResource*>& GetFrames() const { return m_textureFrames; };

    AnimationFrames* AddFrame(const TextureResource* newFrame);

private:

    std::vector<const TextureResource*> m_textureFrames;
    const char* m_name;
};


class ResourceManager {

public:
    static ResourceManager* InitResourceManager(SDL_Renderer* renderer);
    ResourceManager(const ResourceManager&) = delete;
    const ResourceManager& operator=(const ResourceManager&) = delete;
    ~ResourceManager();

    static TextureResource* gameBackgroundTexture;
    static TextureResource* playerTexture;
    static TextureResource* playerLifeTexture;
    static TextureResource* meteorTexture;
    static TextureResource* projectileTexture;
    static TextureResource* pickupTexture;
    static TextureResource* ammoTexture;
    static TextureResource* uiBackgroundTexture;
    static TextureResource* uiButton;
    static TextureResource* uiButtonHover;

    static AnimationFrames* meteorDestroyFrames;

    static Mix_Chunk* shootingSound;
    static Mix_Chunk* projectileHitSound;
    static Mix_Chunk* explosionSound;
    static Mix_Chunk* pickUpSound;

    static TTF_Font* mainFont;

    static SDL_Cursor* cursor;

private:

	TextureResource* LoadTexture(const char*, const Vector2& dimensions, const char* path);
    AnimationFrames* CreateAnimationFrames(const char* name);
    TTF_Font* LoadFont(const char* path, int size);
    Mix_Chunk* LoadMixChunk(const char* path);

private:

    ResourceManager(SDL_Renderer* renderer);

    static ResourceManager* s_resourceManager;
    SDL_Renderer* m_renderer;

    std::vector<TextureResource*> m_textures;
    std::vector<AnimationFrames*> m_animationFrames;
    std::vector<TTF_Font*> m_fonts;
    std::vector<Mix_Chunk*> m_sounds;

};
