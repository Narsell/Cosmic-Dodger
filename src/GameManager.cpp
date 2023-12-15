#include <SDL.h>
#include <SDL_image.h>

#include "GameManager.hpp"
#include "RenderWindow.hpp"
#include "WindowBounds.hpp"
#include "CollisionComponent.hpp"
#include "MovementComponent.hpp"
#include "Player.hpp"
#include "Projectile.hpp"
#include "Transform.hpp"

std::list<GameObject*> GameManager::m_gameObjects;

GameManager::GameManager()
    :m_renderWindow(nullptr),
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
    //TODO: Make render window a singleton too, initialize on initialization list!
    m_renderWindow = new RenderWindow(gameTitle, Vector2(windowWidth, windowHeight));

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

    Vector2 windowDimensions = m_renderWindow->GetWindowDimensions();

    windowBounds = SpawnGameObject(
        new WindowBounds(windowDimensions, "Window Bounds")
    );

    Vector2 textureDimensions = Vector2(112, 75);
    Vector2 playerPosition(windowDimensions.x / 2 - textureDimensions.x / 2, 
                           windowDimensions.y - textureDimensions.y - 5);
    Transform playerTransform = Transform(playerPosition);

    RenderWindow::playerTexture = m_renderWindow->LoadTexture("assets/player_ship.png");
    RenderWindow::projectileTexture = m_renderWindow->LoadTexture("assets/laser.png");

    player = SpawnGameObject(
        new Player(playerTransform, RenderWindow::playerTexture, textureDimensions, "Player")
    );


    //Vector2 test(100, 100);
    //const double l = test.Lenght();
    //const double r = Math::GetAngleFromDirection(test);
    //const double angle = 45;
    //const Vector2 dir = Math::GetDirectionFromAngle(angle);
    //test.Normalize();
}

void GameManager::BeginPlay()
{
    CollisionComponent* windowCollision = windowBounds->GetComponentOfType<CollisionComponent>();
    player->GetCollisionComponent()->ListenForCollisions(windowCollision);

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
    m_renderWindow->Clear();

    for (GameObject* gameObject : m_gameObjects) {
        if (gameObject->GetCanRender()) {
            gameObject->Render(m_renderWindow->GetRenderer());
        }
    }

    m_renderWindow->Display();
}


GameManager::~GameManager()
{
    //Deleting all game objects
    for (GameObject* gameObject : m_gameObjects) {
        delete gameObject;
    }

    delete m_renderWindow;
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
