#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>


#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Math.h"
#include "Utils.hpp"
#include "Collider2D.hpp"
#include "SDLApp.hpp"

int main(int argc, char** args)
{
    App* app = App::GetAppInstance();
    app->StartApp();

    return 0;
}