#include "GameManager.hpp"
#include "utilities/Performance.hpp"


void* operator new(size_t size)
{
    AllocationMetrics::GetInstance()->s_totalAllocated += size;
    //std::cout << "Allocating " << size << "bytes\n";
    return malloc(size);
}

void operator delete (void* memory, size_t size)
{
    AllocationMetrics::GetInstance()->s_totalFreed += size;
    //std::cout << "Freeing " << size << "bytes\n";
    free(memory);
}

int main(int argc, char** args)
{
    GameManager* app = GameManager::GetInstance();
    app->GameStart("Game v.1.0");
    return 0;
}