#pragma once
#include <SDL.h>
#include <list>

class App {

public:

	static App* GetAppInstance();
	void StartApp();

	App(const App& other) = delete;
	const App& operator=(const App& other) = delete;
	~App();

private:

	App();

	void Construction();
	void BeginPlay();
	void HandleEvents();
	void Update();
	void Render();

private:
	static App* app;
	bool isAppRunning = true;
	class RenderWindow* renderWindow = nullptr;
	SDL_Event event;

	// Game entities
	std::list<class Entity*> entities;
	Entity* wilson = nullptr;
	Entity* robert = nullptr;

};
