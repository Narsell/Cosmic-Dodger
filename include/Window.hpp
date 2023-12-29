#pragma once
#include <list>

#include "Math.hpp"

struct TextureResource {

public:

    TextureResource(const char* name, const Vector2 dimensions, SDL_Texture* texture)
        :
        m_name(name),
        m_dimensions(dimensions),
        m_texture(texture)
    {}

    ~TextureResource() {
        if (m_texture) {
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

class Window {

public:
    //TODO: Make it a singleton... or not????
    Window(const char* title);
    Window(const Vector2& other) = delete;
    const Vector2& operator=(const Vector2& other) = delete;
    ~Window();

    static int s_width;
    static int s_height;

    TextureResource* LoadTexture(const char* name, const Vector2& dim, const char* filePath);

    struct SDL_Renderer* GetRenderer() const { return m_renderer; };

    void Clear();
	void Display();

    static TextureResource* playerTexture;
    static TextureResource* projectileTexture;

private:

    struct SDL_Window* m_window;
    struct SDL_Renderer* m_renderer;
};