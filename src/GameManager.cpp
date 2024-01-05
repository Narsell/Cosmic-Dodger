#include <SDL.h>
#include <SDL_image.h>

#include "GameManager.hpp"
#include "Window.hpp"
#include "WindowBounds.hpp"
#include "CollisionComponent.hpp"
#include "MovementComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Transform.hpp"
#include "Utils.hpp"

std::list<GameObject*> GameManager::m_gameObjects;
std::vector<GameObject*> GameManager::m_destroyQueue;
std::vector<SDL_Event> GameManager::m_inputEventQueue;
const Uint8* GameManager::m_keyboardState;

GameManager::GameManager(const Uint32 subSystems)
    :m_window(nullptr),
    m_isGameRunning(true)
{
    if (SDL_Init(subSystems) < 0) {
        std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
    }

}

GameManager* GameManager::GetInstance()
{
    static GameManager app(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    return &app;
}

void GameManager::GameStart(const char* gameTitle)
{
    m_window = new Window(gameTitle);

    Construction();
    BeginPlay();
    float frameEndTime = static_cast<float>(SDL_GetPerformanceCounter());
    float frameStartTime = 0;

    while (m_isGameRunning) {
        frameStartTime = frameEndTime;
        frameEndTime = static_cast<float>(SDL_GetPerformanceCounter());
        HandleInput();
        Update((frameEndTime - frameStartTime) / SDL_GetPerformanceFrequency());
        ClearEventQueue();
        Render();
    }
    SDL_Quit();
}

void GameManager::Construction()
{
    windowBounds = SpawnGameObject(new WindowBounds("Window Bounds"));

    Vector2 playerDimensions = Vector2(112, 75);
    Vector2 playerPosition(Window::s_width / 2 - playerDimensions.x / 2,
                           Window::s_height - playerDimensions.y - 5);
    Transform playerTransform = Transform(playerPosition);

    Window::playerTexture = m_window->LoadTexture("Player", playerDimensions, "assets/player_ship.png");
    Window::projectileTexture = m_window->LoadTexture("Projectile", Vector2(9, 37), "assets/laser.png");

    player = SpawnGameObject(
        new Player(playerTransform, Window::playerTexture, "Player")
    );
}

void GameManager::BeginPlay()
{
    player->SetWindowBounds(windowBounds);
}

void GameManager::HandleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        m_inputEventQueue.push_back(event);

        if (event.type == SDL_QUIT) {
            m_isGameRunning = false;
        }
    }

    m_keyboardState = SDL_GetKeyboardState(NULL);
    
}


void GameManager::Update(const float deltaTime)
{
    for (GameObject* destroyedGameObj : m_destroyQueue) {
        assert(destroyedGameObj);
        delete destroyedGameObj;
        m_gameObjects.remove(destroyedGameObj);
    }
    m_destroyQueue.clear();

    for (GameObject* gameObject : m_gameObjects) {
        assert(gameObject);
        if (gameObject->GetCanUpdate()) {
            gameObject->Update(deltaTime);
        }
    }

    //std::cout << "fps: " << 1 / (deltaTime) << "\n";
    //std::cout << AllocationMetrics::GetInstance()->CurrentUsage() << std::endl;
}

void GameManager::ClearEventQueue()
{
    m_inputEventQueue.clear();
}

void GameManager::Render()
{
    m_window->Clear();

    for (GameObject* gameObject : m_gameObjects) {
        if (gameObject->GetCanRender()) {
            gameObject->Render(m_window->GetRenderer());
        }
    }

    m_window->Display();
}


GameManager::~GameManager()
{
    //Deleting all game objects
    for (GameObject* gameObject : m_gameObjects) {
        delete gameObject;
    }

    delete m_window;
    std::cout << AllocationMetrics::GetInstance()->CurrentUsage() << std::endl;

}



