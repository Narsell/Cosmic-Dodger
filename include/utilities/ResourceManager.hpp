#pragma once
#include <assert.h>
#include <vector>
#include "SDL.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "utilities/Math.hpp"


struct TextureResource {

public:

    TextureResource(const char* name, const Vector2 dimensions, SDL_Texture* texture)
        :
        m_name(name),
        m_dimensions(dimensions),
        m_texture(texture)
    {}

    ~TextureResource() {
        assert(m_texture);
        SDL_DestroyTexture(m_texture);
        
    }

    const char* GetName() const { return m_name; };
    const Vector2& GetDimensions() const { return m_dimensions; };
    SDL_Texture* GetTexture() const { return m_texture; };

private:
    const char* m_name;
    const Vector2 m_dimensions;
    SDL_Texture* m_texture;
};

class ResourceManager {

public:

    static TextureResource* playerTexture;
    static TextureResource* meteorTexture;
    static TextureResource* projectileTexture;
    static TextureResource* backgroundTexture;
    static TextureResource* pickupTexture;

    static Mix_Chunk* shootingSound;
    static Mix_Chunk* pickUpSound;

    static TTF_Font* mainFont;

    ~ResourceManager();
    static ResourceManager* InitResourceManager(SDL_Renderer* renderer);
	TextureResource* LoadTexture(const char* name, const Vector2& dimensions, const char* path);
    TTF_Font* LoadFont(const char* path, int size);
    Mix_Chunk* LoadMixChunk(const char* path);


private:

    ResourceManager(SDL_Renderer* renderer);

    static ResourceManager* s_resourceManager;
    SDL_Renderer* m_renderer;

    //TODO: Add vector member variables to store resources and delete them in a for loop.
    std::vector<TextureResource*> m_textures;
    std::vector<TTF_Font*> m_fonts;
    std::vector<Mix_Chunk*> m_sounds;

};
