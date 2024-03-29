#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include <glm/gtx/color_space.hpp>
#include "Mesh.h"

const int width = 400;
const int height = 300;
const int samples = 20;
const int depth = 5;

void InitScene01(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    // create objects -> add to scene
    for (int x = -10; x < 10; x++)
    {
        for (int z = -10; z < 10; z++)
        {
            std::shared_ptr<Material> material;

            // create random material
            float r = random01();
            if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
            else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
            else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
            else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

            // set random sphere radius
            float radius = random(0.2f, 0.3f);
            // create sphere using random radius and material
            auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
            // add sphere to the scene
            scene.AddObject(std::move(sphere));
        }
    }

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
    scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
    scene.AddObject(std::move(triangle));

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
    scene.AddObject(std::move(plane));

    auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
    mesh->Load("Models/cube-1.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
    scene.AddObject(std::move(mesh));
}

void InitScene03(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 4 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 45.0f, aspectRatio);
    scene.SetCamera(camera);

    // Create Cornell Box walls
    auto leftWall = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.12f, 0.45f, 0.15f }));
    leftWall->Load("Models/quad-1.obj", glm::vec3{ -2, 0, 0 }, glm::vec3{ 0, 90, 0 });
    scene.AddObject(std::move(leftWall));

    auto rightWall = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.65f, 0.05f, 0.05f }));
    rightWall->Load("Models/quad-1.obj", glm::vec3{ 2, 0, 0 }, glm::vec3{ 0, -90, 0 });
    scene.AddObject(std::move(rightWall));

    auto backWall = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.73f, 0.73f, 0.73f }));
    backWall->Load("Models/quad-1.obj", glm::vec3{ 0, 0, -2 }, glm::vec3{ 0, 0, 0 });
    scene.AddObject(std::move(backWall));

    auto floor = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0.73f, 0.73f, 0.73f }));
    floor->Load("Models/quad-1.obj", glm::vec3{ 0, -1, 0 }, glm::vec3{ -90, 0, 0 });
    scene.AddObject(std::move(floor));

    // Create Cornell Box cubes
    auto cube1 = std::make_unique<Sphere>(glm::vec3{ -0.5f, 0, 0.5f }, 0.5f, std::make_shared<Metal>(color3_t{ 0.8f, 0.8f, 0.8f }, 0.3f));
    scene.AddObject(std::move(cube1));

    auto cube2 = std::make_unique<Sphere>(glm::vec3{ 0.5f, 0, -0.5f }, 0.5f, std::make_shared<Lambertian>(color3_t{ 0.8f, 0.3f, 0.3f }));
    scene.AddObject(std::move(cube2));
}

int main(int argc, char* argv[]) {
    std::cout << "Hello, world!" << std::endl;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", width, height);

    Canvas canvas(width, height, renderer);
    Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });

    InitScene01(scene, canvas);

    // render scene
    canvas.Clear({ 0, 0, 0, 1 });
    scene.Render(canvas, samples, depth);
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