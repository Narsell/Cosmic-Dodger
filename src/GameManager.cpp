#include <SDL.h>
#include <SDL_image.h>

#include "GameManager.hpp"
#include "Renderer.hpp"
#include "WindowBounds.hpp"
#include "CollisionComponent.hpp"
#include "MovementComponent.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Transform.hpp"

std::list<GameObject*> GameManager::m_gameObjects;

GameManager::GameManager()
    :m_renderer(nullptr),
    m_isGameRunning(true)
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "SDL_Init HA FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << std::endl;
    }
}

GameManager* GameManager::GetInstance()
{
    static GameManager app;
    return &app;
}

void GameManager::GameStart(const char* gameTitle, const float windowWidth, const float windowHeight)
{
    m_renderer = new Renderer(gameTitle, Vector2(windowWidth, windowHeight));

    Construction();
    BeginPlay();
    while (m_isGameRunning) {
        HandleInput();
        Update(1.f);
        Render();
        ClearFrameEvents();
    }
    SDL_Quit();
}

void GameManager::Construction()
{

    Vector2 windowDimensions = m_renderer->GetWindowDimensions();

    windowBounds = SpawnGameObject(
        new WindowBounds(windowDimensions, "Window Bounds")
    );

    Vector2 playerDimensions = Vector2(112, 75);
    Vector2 playerPosition(windowDimensions.x / 2 - playerDimensions.x / 2,
                           windowDimensions.y - playerDimensions.y - 5);
    Transform playerTransform = Transform(playerPosition);

    Renderer::playerTexture = m_renderer->LoadTexture("Player", playerDimensions, "assets/player_ship.png");
    Renderer::projectileTexture = m_renderer->LoadTexture("Projectile", Vector2(9, 37), "assets/laser.png");

    player = SpawnGameObject(
        new Player(playerTransform, Renderer::playerTexture, "Player")
    );
}

void GameManager::BeginPlay()
{
    player->SetWindowBounds(windowBounds);
}

void GameManager::HandleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        GetFrameEvents().push_back(event);
    }

    for (SDL_Event& frameEvent : GetFrameEvents()) {
        if (frameEvent.type == SDL_QUIT) {
            m_isGameRunning = false;
        }
    }
}


void GameManager::Update(const float deltaTime)
{

    for (GameObject* gameObject : m_gameObjects) {
        if (gameObject->GetCanUpdate()) {
            gameObject->Update(deltaTime);
        }
    }
}

void GameManager::Render()
{
    m_renderer->Clear();

    for (GameObject* gameObject : m_gameObjects) {
        if (gameObject->GetCanRender()) {
            gameObject->Render(m_renderer->GetRenderer());
        }
    }

    m_renderer->Display();
}


GameManager::~GameManager()
{
    //Deleting all game objects
    for (GameObject* gameObject : m_gameObjects) {
        delete gameObject;
    }

    delete m_renderer;
}

std::vector<SDL_Event>& GameManager::GetFrameEvents()
{
    static std::vector<SDL_Event> frameEvents;
    return frameEvents;
}

void GameManager::ClearFrameEvents()
{
    GetFrameEvents().clear();
}
