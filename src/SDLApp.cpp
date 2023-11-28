#include <SDL.h>
#include <SDL_image.h>

#include "SDLApp.hpp"
#include "RenderWindow.hpp"
#include "Entity.hpp"

App* App::app = nullptr;

App::App()
    :renderWindow(nullptr),
    isAppRunning(true)
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "SDL_Init HA FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << std::endl;
    }
    //TODO: Make render window a singleton too, initialize on initialization list!
    renderWindow = new RenderWindow("GAME v1.0", Vector2(1280, 720));
}

App* App::GetAppInstance()
{
    if (!app) {
        app = new App();
    }
    return app;
}

void App::StartApp()
{
    Construction();
    BeginPlay();
    while (isAppRunning) {
        HandleEvents();
        Update();
        Render();
    }
    SDL_Quit();
    //Construction: To construct entities.
    //Begin play: To do more setup with entities and their components
    //            so they can guarantee all other entities have been created.
    //Game loop
        //Delate to update loops
        //Delegate to render loops
    //App end: Free memory, etc..

}

void App::Construction()
{
    SDL_Texture* grassTexture = renderWindow->LoadTexture("assets/ground_tile.png");

    wilson = new Entity(Vector2(0, 0), grassTexture);
    robert = new Entity(Vector2(0, 688), grassTexture);

    wilson->AddCollider(Vector2(32), Vector2::ZERO, true);

    wilson->SetVelocity(Vector2(5, 5));

    robert->AddCollider(Vector2(32), Vector2::ZERO, true);

    robert->SetVelocity(Vector2(5, -5));

   entities.push_back(wilson);
   entities.push_back(robert);

}

void App::BeginPlay()
{
}

void App::HandleEvents()
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT) {
            isAppRunning = false;
        }
    }
}

void App::Update()
{
    for (Entity* entity : entities) {
        entity->Update();
    }


    // bounce on walls
    if ((wilson->GetPosition().x + wilson->GetCurrentFrame().w) >= renderWindow->GetWindowDimensions().x || wilson->GetPosition().x <= 0) {
        Vector2 velocity = wilson->GetVelocity();
        wilson->SetVelocity(Vector2(-velocity.x, velocity.y));
    }
    else if ((wilson->GetPosition().y + wilson->GetCurrentFrame().h) >= renderWindow->GetWindowDimensions().y || wilson->GetPosition().y <= 0) {
        Vector2 velocity = wilson->GetVelocity();
        wilson->SetVelocity(Vector2(velocity.x, -velocity.y));
    }

    if ((robert->GetPosition().x + robert->GetCurrentFrame().w) >= renderWindow->GetWindowDimensions().x || robert->GetPosition().x <= 0) {
        Vector2 velocity = robert->GetVelocity();
        robert->SetVelocity(Vector2(-velocity.x, velocity.y));
    }
    else if ((robert->GetPosition().y + robert->GetCurrentFrame().h) >= renderWindow->GetWindowDimensions().y || robert->GetPosition().y <= 0) {
        Vector2 velocity = robert->GetVelocity();
        robert->SetVelocity(Vector2(velocity.x, -velocity.y));
    }

    if (wilson->HasCollided(*robert)) {
        std::cout << "Collided at ";
        wilson->GetPosition().Print();
    }
}

void App::Render()
{
    renderWindow->Clear();
    for (Entity* entity : entities) {
        renderWindow->Render(*entity);
    }
    renderWindow->Display();
}


App::~App()
{
    if(renderWindow)
        delete renderWindow;
}




