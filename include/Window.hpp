#pragma once
#include <list>

#include "utilities/Math.hpp"

struct SDL_Window;
struct SDL_Renderer;

class Window {

public:
    //TODO: Make it a singleton... or not????
    Window(const char* title);
    Window(const Vector2& other) = delete;
    const Vector2& operator=(const Vector2& other) = delete;
    ~Window();

    static int s_width;
    static int s_height;

    SDL_Renderer* GetRenderer() { return m_renderer; };

    void Clear();
	void Display();

private:

    struct SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};