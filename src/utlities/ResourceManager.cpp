#include <SDL_ttf.h>
#include <SDL_image.h>
#include <assert.h>

#include "userinterface/UIStaticText.hpp"
#include "utilities/ResourceManager.hpp"
#include "Window.hpp"

/* Singleton instance of ResourceManager */
ResourceManager* ResourceManager::s_resourceManager = nullptr;

/* TEXTURES */
TextureResource* ResourceManager::gameBackgroundTexture = nullptr;
TextureResource* ResourceManager::uiBackgroundTexture = nullptr;
TextureResource* ResourceManager::playerTexture = nullptr;
TextureResource* ResourceManager::playerLifeTexture = nullptr;
TextureResource* ResourceManager::meteorTexture = nullptr;
TextureResource* ResourceManager::projectileTexture = nullptr;
TextureResource* ResourceManager::pickupTexture = nullptr;
TextureResource* ResourceManager::ammoTexture = nullptr;

/* ANIMATIONS */

AnimationFrames* ResourceManager::meteorDestroyFrames = nullptr;

/* SOUNDS */
Mix_Chunk* ResourceManager::shootingSound = nullptr;
Mix_Chunk* ResourceManager::projectileHitSound;
Mix_Chunk* ResourceManager::explosionSound = nullptr;
Mix_Chunk* ResourceManager::pickUpSound = nullptr;

/* FONTS */
TTF_Font* ResourceManager::mainFont = nullptr;

/* CURSOR */
SDL_Cursor* ResourceManager::cursor = nullptr;



ResourceManager::ResourceManager(SDL_Renderer* renderer)
	:m_renderer(renderer)
{
	Vector2 bgDimensions = Vector2(1280.f, 720.f);
	Vector2 uibgDimensions = Vector2(450.f, 450.f);
	Vector2 playerDimensions = Vector2(112.f, 75.f);
	Vector2 playerLifeDimensions = Vector2(37.f, 26.f);
	Vector2 meteorDimensions = Vector2(89.f, 82.f);
	Vector2 projectileDimensions = Vector2(9.f, 54.f);
	Vector2 pickupDimensions = Vector2(30.f, 31.f);
	Vector2 ammoDimensions = Vector2(12.f, 20.f);

	ResourceManager::gameBackgroundTexture = LoadTexture("Background", bgDimensions, "assets/background.png");
	ResourceManager::uiBackgroundTexture = LoadTexture("UI Background", uibgDimensions, "assets/ui_bg.png");
	ResourceManager::playerTexture = LoadTexture("Player", playerDimensions, "assets/player_ship.png");
	ResourceManager::playerLifeTexture = LoadTexture("Player Life", playerLifeDimensions, "assets/player_life.png");
	ResourceManager::meteorTexture = LoadTexture("Meteor", meteorDimensions, "assets/meteors/meteor3.png");
	ResourceManager::projectileTexture = LoadTexture("Projectile", projectileDimensions, "assets/laser_g.png");
	ResourceManager::pickupTexture = LoadTexture("Pickup", pickupDimensions, "assets/star_gold.png");
	ResourceManager::ammoTexture = LoadTexture("Ammo", ammoDimensions, "assets/ammo_green.png");

	Vector2 meteorFramesDimensions = Vector2(100.f, 100.f);
	ResourceManager::meteorDestroyFrames = CreateAnimationFrames("Meteor Destruction");
	ResourceManager::meteorDestroyFrames->AddFrame(
		LoadTexture("Meteor Frame 1", meteorFramesDimensions, "assets/meteors/animations/destroy_0.png")
	)->AddFrame(
		LoadTexture("Meteor Frame 2", meteorFramesDimensions, "assets/meteors/animations/destroy_1.png")
	)->AddFrame(
		LoadTexture("Meteor Frame 3", meteorFramesDimensions, "assets/meteors/animations/destroy_2.png")
	)->AddFrame(
		LoadTexture("Meteor Frame 4", meteorFramesDimensions, "assets/meteors/animations/destroy_3.png")
	)->AddFrame(
		LoadTexture("Meteor Frame 5", meteorFramesDimensions, "assets/meteors/animations/destroy_4.png")
	)->AddFrame(
		LoadTexture("Meteor Frame 6", meteorFramesDimensions, "assets/meteors/animations/destroy_5.png")
	)->AddFrame(
		LoadTexture("Meteor Frame 7", meteorFramesDimensions, "assets/meteors/animations/destroy_6.png")
	);

	SDL_Surface* cursorSurface = IMG_Load("assets/crossair_red.png");
	ResourceManager::cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
	SDL_FreeSurface(cursorSurface);
	
	ResourceManager::shootingSound = LoadMixChunk("assets/shoot1.wav");
	ResourceManager::projectileHitSound = LoadMixChunk("assets/hit.wav");
	ResourceManager::explosionSound = LoadMixChunk("assets/explosion.wav");
	ResourceManager::pickUpSound = LoadMixChunk("assets/pickup.wav");

	ResourceManager::mainFont = LoadFont("assets/LilitaOne-Regular.ttf", 50);

}

ResourceManager::~ResourceManager()
{
	for (TextureResource*& textureRes : m_textures) {
		delete textureRes;
	}

	for (AnimationFrames*& frames : m_animationFrames) {
		delete frames;
	}

	for (TTF_Font*& font : m_fonts) {
		TTF_CloseFont(font);
	}

	for (Mix_Chunk*& sound_mix : m_sounds) {
		Mix_FreeChunk(sound_mix);
	}

	SDL_FreeCursor(cursor);
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
	assert(texture);
	if (!texture)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	return m_textures.emplace_back(new TextureResource(name, dimensions, texture));
}

AnimationFrames* ResourceManager::CreateAnimationFrames(const char* name)
{
	return m_animationFrames.emplace_back(new AnimationFrames(name));
}

TTF_Font* ResourceManager::LoadFont(const char* path, int size)
{
	TTF_Font* font = nullptr;
	font = TTF_OpenFont(path, size);
	assert(font);
	if (!font)
		std::cout << "Failed to load font. Error: " << SDL_GetError() << std::endl;
	m_fonts.push_back(font);
	return m_fonts.back();
}

Mix_Chunk* ResourceManager::LoadMixChunk(const char* path)
{
	Mix_Chunk* mixChunk = nullptr;
	mixChunk = Mix_LoadWAV(path);
	assert(mixChunk);
	if(!mixChunk)
		std::cout << "Failed to load audio. Error: " << Mix_GetError() << std::endl;
	m_sounds.push_back(mixChunk);
	return m_sounds.back();
}



AnimationFrames::AnimationFrames(const char* name)
	:m_name(name)
{
}

AnimationFrames* AnimationFrames::AddFrame(const TextureResource* newFrame)
{
	m_textureFrames.push_back(newFrame);
	return this;
}

TextureResource::TextureResource(const char* name, const Vector2& dimensions, SDL_Texture* texture)
	:m_name(name), m_dimensions(dimensions), m_texture(texture)
{
}



TextureResource::~TextureResource()
{
	assert(m_texture);
	SDL_DestroyTexture(m_texture);
}

