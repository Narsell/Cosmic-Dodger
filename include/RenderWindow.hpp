#pragma once

#include "Math.hpp"

class RenderWindow {
public:
    RenderWindow(const char* title, int width, int height);

    const Vector2& GetWindowDimensions() const { return m_windowDimensions; };
    void CleanUp();
    SDL_Texture* LoadTexture(const char* filePath);
    void Clear();
	void Render(class Entity& entity);
    void Render(const struct SDL_Rect* rect);
	void Display();
private:
    struct SDL_Window* m_window;
    struct SDL_Renderer* m_renderer;
    const Vector2 m_windowDimensions;
};