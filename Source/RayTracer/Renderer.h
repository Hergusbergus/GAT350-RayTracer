#pragma once
#include <iostream>
#include <SDL.h>

class Renderer
{
public:
	Renderer() = default;

	bool Initialize();
	void Shutdown();
	bool CreateWindow(const std::string& title, int width, int height);

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};

