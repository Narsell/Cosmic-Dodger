#include "GameManager.hpp"

int main(int argc, char** args)
{
    GameManager* app = GameManager::GetInstance();
    app->GameStart("Game v.1.0", 1280, 740);

    return 0;
}