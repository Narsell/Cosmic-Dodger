#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <assert.h>

#include "Renderer.hpp"
#include "GameObject.hpp"
#include "Math.hpp"

TextureResource* Renderer::playerTexture;
TextureResource* Renderer::projectileTexture;

Renderer::Renderer(const char* title, const Vector2& windowDimensions)
    :m_window(nullptr), m_renderer(nullptr), m_windowDimensions(windowDimensions)
{
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)windowDimensions.x, (int)windowDimensions.y, SDL_WINDOW_SHOWN);
    if (!m_window){
        std::cout << "Window failed to init. ERROR: " << SDL_GetError() << std::endl;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    delete playerTexture;
    delete projectileTexture;
}

TextureResource* Renderer::LoadTexture(const char* name, const Vector2& dim, const char* filePath){
    SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(m_renderer, filePath);

	if (!texture)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    return new TextureResource(name, dim, texture);
}

void Renderer::Clear(){
    SDL_SetRenderDrawColor(m_renderer, 0x0, 0x0, 0x0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}

void Renderer::Display(){
    SDL_RenderPresent(m_renderer);
}