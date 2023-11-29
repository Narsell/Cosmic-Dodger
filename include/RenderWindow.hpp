#pragma once

#include "Math.hpp"

class RenderWindow {
public:

    RenderWindow(const char* title, const Vector2& windowDimensions);
    RenderWindow(const Vector2& other) = delete;
    const Vector2& operator=(const Vector2& other) = delete;
    ~RenderWindow();

    const Vector2& GetWindowDimensions() const { return m_windowDimensions; };
    SDL_Texture* LoadTexture(const char* filePath);

    //Rendering
    void Clear();
	void Render(class Entity& entity);
    void Render(const struct SDL_Rect* rect);
	void Display();

private:
    struct SDL_Window* m_window;
    struct SDL_Renderer* m_renderer;
    const Vector2 m_windowDimensions;
};