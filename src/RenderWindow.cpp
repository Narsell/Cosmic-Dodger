#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.hpp"
#include "Collider2D.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
    :m_window(nullptr), m_renderer(nullptr), m_windowDimensions(Vector2(width, height))
{
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!m_window){
        std::cout << "Window failed to init. ERROR: " << SDL_GetError() << std::endl;
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}


SDL_Texture* RenderWindow::LoadTexture(const char* filePath){
    SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(m_renderer, filePath);

	if (!texture)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::CleanUp(){
    SDL_DestroyWindow(m_window);
}

void RenderWindow::Clear(){
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);
}

void RenderWindow::Render(Entity& entity){

    SDL_Rect src { 
        entity.GetCurrentFrame().x, 
        entity.GetCurrentFrame().y, 
        entity.GetCurrentFrame().w, 
        entity.GetCurrentFrame().h
    };

    SDL_Rect dst {
        entity.GetPosition().x,
        entity.GetPosition().y,
        entity.GetCurrentFrame().w,
        entity.GetCurrentFrame().h
    };

    //Render entity
    SDL_RenderCopy(m_renderer, entity.GetTexture(), &src, &dst);

    //Render componentes
    for (const Collider2D* collider : entity.GetAllColliders()) {
        if (collider->GetbRenderBounds()) {
            Render(&collider->GetRect());
        }
    }
}

void RenderWindow::Render(const SDL_Rect* rect)
{
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(m_renderer, rect);
}

void RenderWindow::Display(){
    SDL_RenderPresent(m_renderer);
}