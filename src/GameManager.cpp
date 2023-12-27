#include <SDL.h>
#include <SDL_image.h>

#include "GameManager.hpp"
#include "Renderer.hpp"
#include "WindowBounds.hpp"
#include "CollisionComponent.hpp"
#include "MovementComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Transform.hpp"
#include "Utils.hpp"

std::list<GameObject*> GameManager::m_gameObjects;
std::list<GameObject*> GameManager::m_destroyQueue;
std::vector<PlayerInputComponent*> GameManager::suscribedPlayerInputComponents;

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
        utils::HireTimeInSeconds();
        HandleInput();
        Update(1.f);
        Render();
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
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            m_isGameRunning = false;
        }
    }

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

    for (PlayerInputComponent* inputComp : suscribedPlayerInputComponents) {
        inputComp->UpdateKeyboardState(keyboardState);
    }
}


void GameManager::Update(const float deltaTime)
{
    for (GameObject* destroyedGameObj : m_destroyQueue) {
        assert(destroyedGameObj);
        m_gameObjects.remove(destroyedGameObj);
        delete destroyedGameObj;
    }
    m_destroyQueue.clear();

    for (GameObject* gameObject : m_gameObjects) {
        assert(gameObject);
        if (gameObject->GetCanUpdate()) {
            gameObject->Update(deltaTime);
        }
    }
   
    std::cout << "Using " << AllocationMetrics::GetInstance()->CurrentUsage() << " bytes\n";
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
    std::cout << AllocationMetrics::GetInstance()->CurrentUsage() << std::endl;

}

void GameManager::SuscribeToKeyboardEvents(PlayerInputComponent* PlayerInputComponent)
{
    suscribedPlayerInputComponents.push_back(PlayerInputComponent);
}


