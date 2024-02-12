#pragma once
#include <SDL.h>
#include <list>
#include <vector>
#include <sstream>

#include "entities/GameObject.hpp"

class PlayerInputComponent;
class Window;
class GameObject;
class Player;
class WindowBounds;
class ResourceManager;
class HUD;
class GameState;
class MeteorSpawner;
class PickupSpawner;

class GameManager {

public:
	//Gets the GameManager instance
	static GameManager* GetInstance();
	//Initializes the window and starts the game loop.
	void GameStart(const char* gameTitle);

	template<typename T>
	inline static T* SpawnEntity(T* entity);

	template<typename T>
	inline static void DestroyEntity(T* entity);

	//Copy constructor, copy assigment and destructors.
	GameManager(const GameManager& other) = delete;
	const GameManager& operator=(const GameManager& other) = delete;
	~GameManager();

	static Player* GetPlayer() { return m_player; };
	static MeteorSpawner* GetMeteorSpawner() { return m_meteorSpawner; };
	static PickupSpawner* GetPickupSpawner() { return m_pickupSpawner; };

	static std::vector<SDL_Event>& GetInputEventQueue() { return m_inputEventQueue; };
	static const Uint8*& GetInputKeyboardState() { return m_keyboardState; };

private:
	//Private constructor to avoid unwanted initialization.
	GameManager(const Uint32 subSystems);
	//To construct game entities and set them up.
	void Construction();
	//To set the initial state of entities and other actors of the game.
	void BeginPlay();
	//Handles window type inputs and populates the events for that frame.
	void HandleInput();
	//Updates each entity. i.e. Calls each entity Update function and deals with collisions.
	void Update(const float deltaTime);
	//Clears the input event queue.
	void ClearEventQueue();
	//Renders each entity.
	void Render();

private:
	bool m_isGameRunning = true;
	Window* m_window = nullptr;
	ResourceManager* m_resourceManager = nullptr;
	static std::vector<SDL_Event> m_inputEventQueue;
	static const Uint8* m_keyboardState;

	// Game entities
	static std::list<BaseEntity*> m_entities;
	static std::vector<BaseEntity*> m_destroyQueue;
	static Player* m_player;
	static MeteorSpawner* m_meteorSpawner;
	static PickupSpawner* m_pickupSpawner;
	WindowBounds* m_windowBounds = nullptr;

	//UI
	HUD* m_hud = nullptr;

	//GameState
	GameState* m_gameState = nullptr;

};

/* TEMPLATE DEFINITIONS */

template<typename T>
inline T* GameManager::SpawnEntity(T* entity)
{
	assert(entity);
	std::string idName = entity->GetDisplayName() + "_" + std::to_string(m_entities.size());
	entity->SetIdName(idName);
	//std::cout << "Spawned " << entity->GetIdName() << "\n";
	m_entities.emplace_back(entity);
	return entity;
}

template<typename T>
inline void GameManager::DestroyEntity(T* entity)
{
	assert(entity);
	//std::cout << "Destroyed " << entity->GetIdName() << "\n";
	if (std::find(m_destroyQueue.begin(), m_destroyQueue.end(), entity) != m_destroyQueue.end()) 
	{
		std::cout << entity->GetDisplayName() << " already queued for deletion! SKIPPING\n";
		return;
	}
	m_destroyQueue.push_back(entity);
	entity->Disable();
}