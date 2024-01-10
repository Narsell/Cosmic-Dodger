#pragma once
#include "SDL.h"
#include <SDL_ttf.h>

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
        if (m_texture != nullptr) {
            std::cout << "Destroyed TEXTURE " << m_name << "\n";
            SDL_DestroyTexture(m_texture);
        }
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

    ~ResourceManager();

    /* 
    Initializes the Resource Manager and returns a pointer to it.
    If initialized more than once, it will return the first instance initialized everytime.
    */
    static ResourceManager* InitResourceManager(SDL_Renderer* renderer);

	TextureResource* LoadTexture(const char* name, const Vector2& dimensions, const char* path);
    static TTF_Font* LoadFont(const char* path, int size);

    static TextureResource* playerTexture;
    static TextureResource* projectileTexture;
    static TTF_Font* textFont;

private:

    ResourceManager(SDL_Renderer* renderer);

    static ResourceManager* m_resourceManager;
    SDL_Renderer* m_renderer;

    //TODO: Add vector member variables to store resources and delete them in a for loop.

};
