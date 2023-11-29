#include <SDL.h>
#include <SDL_image.h>

#include "GameManager.hpp"
#include "RenderWindow.hpp"
#include "Player.hpp"
#include "Collider2D.hpp"

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

void GameManager::GameStart(const char* gameTitle, int windowWidth, int windowHeight)
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
    constexpr int borderWidth = 10;
    Vector2 windowDimensions = m_renderWindow->GetWindowDimensions();
    windowBounds = new Entity(Vector2::ZERO);
    windowBounds->AddCollider(Vector2(borderWidth, windowDimensions.y), Vector2(0, 0), true);
    windowBounds->AddCollider(Vector2(borderWidth, windowDimensions.y), Vector2(windowDimensions.x - borderWidth, 0), true);
    windowBounds->AddCollider(Vector2(windowDimensions.x, borderWidth), Vector2(0, 0), true);
    windowBounds->AddCollider(Vector2(windowDimensions.x, borderWidth), Vector2(0, windowDimensions.y - borderWidth), true);

    //TODO: Use sharedptr
    SDL_Texture* playerTexture = m_renderWindow->LoadTexture("assets/player_ship.png");

    Vector2 playerPosition = Vector2(100, 100);
    Vector2 textureDimensions = Vector2(112, 75);
    player = new Player(playerPosition, playerTexture, textureDimensions);

    player->AddCollider(Vector2(112, 75), Vector2::ZERO, true);

   m_entities.push_back(player);
   m_entities.push_back(windowBounds);
}

void GameManager::BeginPlay()
{
    player->SetVelocity(Vector2(5, 1));
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

    for (Entity* entity : m_entities) {
        entity->Update(deltaTime);
    }

    //Some collision placeholder bulshi...
    if (windowBounds->GetColliderByIndex(0)->IsColliding(player->GetAllColliders()) ||
        windowBounds->GetColliderByIndex(1)->IsColliding(player->GetAllColliders())
        ) 
    {
        Vector2 bounceVelocity(-player->GetVelocity().x, player->GetVelocity().y);
        player->SetVelocity(bounceVelocity);
    }
    else if (windowBounds->GetColliderByIndex(2)->IsColliding(player->GetAllColliders()) ||
             windowBounds->GetColliderByIndex(3)->IsColliding(player->GetAllColliders())
        ) 
    {
        Vector2 bounceVelocity(player->GetVelocity().x, -player->GetVelocity().y);
        player->SetVelocity(bounceVelocity);
    }
}

void GameManager::Render()
{
    m_renderWindow->Clear();

    for (Entity* entity : m_entities) {
        m_renderWindow->Render(*entity);
    }

    m_renderWindow->Display();
}


GameManager::~GameManager()
{
    if(m_renderWindow)
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




