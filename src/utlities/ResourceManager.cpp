#include <SDL_ttf.h>
#include <SDL_image.h>
#include <assert.h>

#include "userinterface/StaticText.hpp"
#include "utilities/ResourceManager.hpp"
#include "Window.hpp"

/* Singleton instance of ResourceManager */
ResourceManager* ResourceManager::s_resourceManager = nullptr;

/* TEXTURE RESOURCES INSTANCES */
TextureResource* ResourceManager::playerTexture = nullptr;
TextureResource* ResourceManager::meteorTexture = nullptr;
TextureResource* ResourceManager::projectileTexture = nullptr;
TextureResource* ResourceManager::backgroundTexture = nullptr;

/* FONTS */
TTF_Font* ResourceManager::textFont = nullptr;

ResourceManager::ResourceManager(SDL_Renderer* renderer)
	:m_renderer(renderer)
{
	Vector2 playerDimensions = Vector2(112.f, 75.f);
	Vector2 meteorTexture = Vector2(89.f, 82.f);
	Vector2 projectileDimensions = Vector2(9.f, 54.f);
	Vector2 bgDimensions = Vector2(1280.f, 720.f);

	ResourceManager::playerTexture = LoadTexture("Player", playerDimensions, "assets/player_ship.png");
	ResourceManager::meteorTexture = LoadTexture("Meteor", meteorTexture, "assets/meteors/meteor3.png");
	ResourceManager::projectileTexture = LoadTexture("Projectile", projectileDimensions, "assets/laser_g.png");
	ResourceManager::backgroundTexture = LoadTexture("Background", bgDimensions, "assets/background.png");
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
	if (!s_resourceManager) {
		s_resourceManager = new ResourceManager(renderer);
	}
	return s_resourceManager;
}

TextureResource* ResourceManager::LoadTexture(const char* name, const Vector2& dimensions, const char* path)
{
	SDL_Texture* texture = nullptr;
	texture = IMG_LoadTexture(m_renderer, path);

	if (!texture)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	
	return new TextureResource(name, dimensions, texture);
}

TTF_Font* ResourceManager::LoadFont(const char* path, int size)
{
	if (!textFont) {
		textFont = TTF_OpenFont(path, size);
	}
	return textFont;
	
}
