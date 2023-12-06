#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"

int main(int argc, char* argv[]) {
    std::cout << "Hello, world!" << std::endl;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracing Program", 400, 300);

    Canvas canvas(400, 300, renderer);

    float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

    Scene scene(20); // sky color could be set with the top and bottom color
    scene.SetCamera(camera);

    // create material
    auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

    // create material
    auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

    // create objects -> add to scene
    for (int i = 0; i < 50; i++)
    {
        std::shared_ptr<Material> material = (rand() % 2) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
        auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-5, 5), random(-5, 5), 15 }, random(0.2f, 1), material);
        scene.AddObject(std::move(sphere));
    }

    // render scene 
    canvas.Clear({ 0, 0, 0, 1 });
    scene.Render(canvas, 50);
    canvas.Update();

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

        renderer.PresentCanvas(canvas);
    }

    renderer.Shutdown();

    return 0;
}