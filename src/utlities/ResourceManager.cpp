#include <SDL_ttf.h>
#include <SDL_image.h>
#include <assert.h>

#include "userinterface/StaticText.hpp"
#include "utilities/ResourceManager.hpp"
#include "Window.hpp"

/* Singleton instance of ResourceManager */
ResourceManager* ResourceManager::m_resourceManager = nullptr;

/* TEXTURE RESOURCES INSTANCES */
TextureResource* ResourceManager::playerTexture = nullptr;
TextureResource* ResourceManager::projectileTexture = nullptr;

/* FONTS */
TTF_Font* ResourceManager::textFont = nullptr;

ResourceManager::ResourceManager(SDL_Renderer* renderer)
	:m_renderer(renderer)
{
}

ResourceManager::~ResourceManager()
{
	delete playerTexture;
	delete projectileTexture;
	TTF_CloseFont(textFont);
}

ResourceManager* ResourceManager::InitResourceManager(SDL_Renderer* renderer)
{
	assert(renderer);
	if (!m_resourceManager) {
		m_resourceManager = new ResourceManager(renderer);
	}
	return m_resourceManager;
}

TextureResource* ResourceManager::LoadTexture(const char* name, const Vector2& dimensions, const char* path)
{
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(m_renderer, path);

	if (!texture)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	
	return new TextureResource(name, dimensions, texture);
}

const TTF_Font* ResourceManager::LoadFont(const char* path, int size)
{
	if (!textFont) {
		textFont = TTF_OpenFont(path, size);
	}
	return textFont;
	
}
