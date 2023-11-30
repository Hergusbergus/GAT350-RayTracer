#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, world!" << std::endl;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracing Program", 400, 300);

    Canvas canvas(400, 300, renderer);

    bool quit = false;
    while (!quit)
    {
        seedRandom(static_cast<unsigned int>(time(nullptr)));

        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        }

        canvas.Clear({ 0, 0, 0, 1 });
        for (int i = 0; i < 1000; ++i) {
            glm::ivec2 randomPoint{
                static_cast<int>(random(0, canvas.GetSize().x)),
                static_cast<int>(random(0, canvas.GetSize().y))
            };

            color4_t randomColor{
                random01(),  // Red
                random01(),  // Green
                random01(),  // Blue
                1.0f         // Alpha
            };

            canvas.DrawPoint(randomPoint, randomColor);
        }
        canvas.Update();

        renderer.PresentCanvas(canvas);
    }

    renderer.Shutdown();

    return 0;
}