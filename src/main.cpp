#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>


#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.h"
#include "Utils.hpp"
#include "Collider2D.hpp"

int main(int argc, char** args)
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0){
        std::cout << "SDL_Init HA FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG))){
        std::cout << "IMG_Init has failed. Error: " << SDL_GetError() << std::endl;
    }
    RenderWindow window("GAME v1.0", 1280, 720);

    //GOOD CANDIDATE FOR SHARED PTR
    SDL_Texture* grassTexture = window.LoadTexture("assets/ground_tile.png");

    Entity wilson(Vector2(0, 0), grassTexture);
    Entity robert(Vector2(0, 688), grassTexture);
    wilson.AddCollider(Vector2(32), Vector2::ZERO, true);
    //wilson.AddCollider(Vector2(32), Vector2(32, 0), true);

    robert.AddCollider(Vector2(32), Vector2::ZERO, true);
    //robert.AddCollider(Vector2(32), Vector2(0, 32), true);

    Vector2 wilsonDelta = Vector2(2, 2);
    Vector2 robertDelta = Vector2(2, -2);

    bool gameRunning = true;
    SDL_Event event;

    constexpr float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = utils::HireTimeInSeconds();

    while(gameRunning)
    {
        /* FRAME CAPPING BS*/
        {
            float newTime = utils::HireTimeInSeconds();
            float frameTime = newTime - currentTime;

            currentTime = newTime;
            accumulator += frameTime;

            while (accumulator >= timeStep) {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT) {
                        gameRunning = false;
                    }
                }
                accumulator -= timeStep;
            }

            const float alpha = accumulator / timeStep;
        }
        /* FRAME CAPPING BS */

        wilson.AddPositionDelta(wilsonDelta);
        robert.AddPositionDelta(robertDelta);

        // Bounce on walls
        if ((wilson.GetPosition().x + wilson.GetCurrentFrame().w) >= window.GetWindowDimensions().x || wilson.GetPosition().x <= 0) {
            wilsonDelta = Vector2(-wilsonDelta.x, wilsonDelta.y);
        }
        else if ((wilson.GetPosition().y + wilson.GetCurrentFrame().h) >= window.GetWindowDimensions().y || wilson.GetPosition().y <= 0) {
            wilsonDelta = Vector2(wilsonDelta.x, -wilsonDelta.y);
        }

        if ((robert.GetPosition().x + robert.GetCurrentFrame().w) >= window.GetWindowDimensions().x || robert.GetPosition().x <= 0) {
            robertDelta = Vector2(-robertDelta.x, robertDelta.y);
        }
        else if ((robert.GetPosition().y + robert.GetCurrentFrame().h) >= window.GetWindowDimensions().y || robert.GetPosition().y <= 0) {
            robertDelta = Vector2(robertDelta.x, -robertDelta.y);
        }

        wilson.Update();
        robert.Update();

        if (wilson.HasCollided(robert)) {
            //wilsonDelta *= -1;
            //robertDelta *= -1;
            std::cout << "Collided at ";
            wilson.GetPosition().Print();
        }

        window.Clear();

        window.Render(wilson);
        window.Render(robert);

        window.Display();
    }

    window.CleanUp();
    SDL_Quit();
    return 0;
}