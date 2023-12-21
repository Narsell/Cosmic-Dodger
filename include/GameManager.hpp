#pragma once
#include <SDL.h>
#include <list>
#include <vector>
#include "GameObject.hpp"

class PlayerInputComponent;
class Renderer;
class Player;
class WindowBounds;

class GameManager {

public:
	//Gets the GameManager instance
	static GameManager* GetInstance();
	//Calls the appropiate functions to setup the game loop.
	void GameStart(const char* gameTitle, const float windowWidth, const float windowHeight);

	template<typename T>
	static T* SpawnGameObject(T* gameObject);

	template<typename T>
	static void DestroyGameObject(T* gameObject);

	//Copy constructor, copy assigment and destructors.
	GameManager(const GameManager& other) = delete;
	const GameManager& operator=(const GameManager& other) = delete;
	~GameManager();

	static void SuscribeToKeyboardEvents(PlayerInputComponent* PlayerInputComponent);

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
	Renderer* m_renderer = nullptr;
	static std::vector<PlayerInputComponent*> suscribedPlayerInputComponents;

	// Game entities
	static std::list<class GameObject*> m_gameObjects;
	Player* player = nullptr;
	WindowBounds* windowBounds = nullptr;

};

/* TEMPLATE DEFINITIONS */

template<typename T>
T* GameManager::SpawnGameObject(T* gameObject)
{
	assert(gameObject);
	m_gameObjects.emplace_back(gameObject);
	return gameObject;
}

template<typename T>
inline void GameManager::DestroyGameObject(T* gameObject)
{
	//TODO: Rework this so objets are destroyed on the next tick!
	assert(gameObject);
	m_gameObjects.remove(gameObject);
	delete gameObject;
}
