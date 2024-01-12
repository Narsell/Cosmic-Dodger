#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GameManager.hpp"
#include "Window.hpp"
#include "entities/WindowBounds.hpp"
#include "components/CollisionComponent.hpp"
#include "components/MovementComponent.hpp"
#include "components/PlayerInputComponent.hpp"
#include "entities/Player.hpp"
#include "entities/Projectile.hpp"
#include "utilities/Performance.hpp"
#include "utilities/ResourceManager.hpp"
#include "userinterface/HUD.hpp"
#include "utilities/GameState.hpp"

std::list<GameObject*> GameManager::m_gameObjects;
std::vector<GameObject*> GameManager::m_destroyQueue;
std::vector<SDL_Event> GameManager::m_inputEventQueue;
const Uint8* GameManager::m_keyboardState;

GameManager::GameManager(const Uint32 subSystems)
{
    if (SDL_Init(subSystems) < 0) {
        std::cout << "SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
    }
    if (TTF_Init() < 0) {
        std::cout << "TTF_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
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
    
    m_resourceManager = ResourceManager::InitResourceManager(m_window->GetRenderer());

    Construction();
    BeginPlay();
    Uint64 frameEndTime = SDL_GetPerformanceCounter();
    Uint64 frameStartTime = 0;

    while (m_isGameRunning) {
        frameStartTime = frameEndTime;
        frameEndTime = SDL_GetPerformanceCounter();
        HandleInput();
        Update(static_cast<float>(frameEndTime - frameStartTime) / static_cast<float>(SDL_GetPerformanceFrequency()));
        ClearEventQueue();
        Render();
    }
    SDL_Quit();
}

void GameManager::Construction()
{
    m_gameState = GameState::GetGameState();
    m_hud = new HUD(m_window);
    m_gameState->SetTargetHUD(m_hud);

    windowBounds = SpawnGameObject(new WindowBounds("Window Bounds"));

    Vector2 playerDimensions = Vector2(112, 75);
    Vector2 playerPosition(Window::s_width / 2 - playerDimensions.x / 2,
                           Window::s_height - playerDimensions.y - 5);
    Transform playerTransform = Transform(playerPosition);

    ResourceManager::playerTexture = m_resourceManager->LoadTexture("Player", playerDimensions, "assets/player_ship.png");
    ResourceManager::projectileTexture = m_resourceManager->LoadTexture("Projectile", Vector2(9, 37), "assets/laser.png");
    ResourceManager::backgroundTexture = m_resourceManager->LoadTexture("Background", Vector2(1280, 720), "assets/background.png");

    player = SpawnGameObject(
        new Player(playerTransform, ResourceManager::playerTexture, m_hud, "Player")
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

    m_hud->Update(deltaTime);

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

    m_hud->Render(m_window->GetRenderer());

    m_window->Display();
}


GameManager::~GameManager()
{
    //Deleting all game objects
    for (GameObject* gameObject : m_gameObjects) {
        delete gameObject;
    }

    delete m_window;
    delete m_resourceManager;
    delete m_hud;

    std::cout << AllocationMetrics::GetInstance()->CurrentUsage() << std::endl;

}



