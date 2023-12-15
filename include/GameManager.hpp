#pragma once
#include <SDL.h>
#include <list>
#include <vector>
#include "GameObject.hpp"

class GameManager {

public:
	//Gets the GameManager instance
	static GameManager* GetInstance();
	//Calls the appropiate functions to setup the game loop.
	void GameStart(const char* gameTitle, const float windowWidth, const float windowHeight);

	template<typename T>
	static T* SpawnGameObject(T* gameObject);

	//Copy constructor, copy assigment and destructors.
	GameManager(const GameManager& other) = delete;
	const GameManager& operator=(const GameManager& other) = delete;
	~GameManager();
	
	//Gets the queue of events available for that frame.
	static std::vector<SDL_Event>& GetFrameEvents();
	//Clears the event queue, should be done after finishing a frame.
	void ClearFrameEvents();

private:
	//Private constructor to avoid unwanted initialization.
	GameManager();
	//To construct game entities and set them up.
	void Construction();
	//To set the initial state of entities and other actors of the game.
	void BeginPlay();
	//Handles window type inputs and populates the events for that frame.
	void HandleInput();
	//Updates each entity. i.e. Calls each entity Update function and deals with collisions.
	void Update(const float deltaTime);
	//Renders each entity.
	void Render();

private:
	bool m_isGameRunning = true;
	class RenderWindow* m_renderWindow = nullptr;

	// Game entities
	static std::list<class GameObject*> m_gameObjects;
	class Player* player = nullptr;
	class WindowBounds* windowBounds = nullptr;

};

template<typename T>
T* GameManager::SpawnGameObject(T* object)
{
	m_gameObjects.emplace_back(object);
	return object;
}