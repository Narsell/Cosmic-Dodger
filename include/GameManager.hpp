#pragma once
#include <SDL.h>
#include <list>
#include <vector>
#include <sstream>

#include "GameObject.hpp"

class PlayerInputComponent;
class Window;
class GameObject;
class Player;
class WindowBounds;

class GameManager {

public:
	//Gets the GameManager instance
	static GameManager* GetInstance();
	//Calls the appropiate functions to setup the game loop.
	void GameStart(const char* gameTitle);

	template<typename T>
	static T* SpawnGameObject(T* gameObject);

	template<typename T>
	static void DestroyGameObject(T* gameObject);

	//Copy constructor, copy assigment and destructors.
	GameManager(const GameManager& other) = delete;
	const GameManager& operator=(const GameManager& other) = delete;
	~GameManager();

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
	static std::vector<GameObject*> m_destroyQueue;
	static std::vector<SDL_Event> m_inputEventQueue;
	static const Uint8* m_keyboardState;

	// Game entities
	static std::list<GameObject*> m_gameObjects;
	Player* player = nullptr;
	WindowBounds* windowBounds = nullptr;

};

/* TEMPLATE DEFINITIONS */

template<typename T>
T* GameManager::SpawnGameObject(T* gameObject)
{
	assert(gameObject);
	std::string idName = gameObject->GetDisplayName() + "_" + std::to_string(m_gameObjects.size());
	gameObject->SetIdName(idName);
	//std::cout << "Spawned " << gameObject->GetIdName() << "\n";
	m_gameObjects.emplace_back(gameObject);
	return gameObject;
}

template<typename T>
void GameManager::DestroyGameObject(T* gameObject)
{
	assert(gameObject);
	//std::cout << "Destroyed " << gameObject->GetIdName() << "\n";
	m_destroyQueue.push_back(gameObject);
	gameObject->Disable();
}
