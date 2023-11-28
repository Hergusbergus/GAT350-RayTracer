#include <iostream>
#include <SDL.h>
#include "Renderer.h"

int main() {
    std::cout << "Hello, world!" << std::endl;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracing Program", 400, 300);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }
    }

    renderer.Shutdown();

    return 0;
}