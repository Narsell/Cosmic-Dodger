#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>


#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.h"
#include "Utils.hpp"
#include "Collider2D.hpp"
#include "GameManager.hpp"

int main(int argc, char** args)
{
    GameManager* app = GameManager::GetInstance();
    app->GameStart("Game v.1.0", 1280, 740);

    return 0;
}