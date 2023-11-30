#include "Renderer.h"
#include <SDL.h>

bool Renderer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::Shutdown()
{
	if (window != 0) SDL_DestroyWindow(window);
	if (m_renderer != 0) SDL_DestroyRenderer(m_renderer);

	SDL_Quit();
}

bool Renderer::CreateWindow(const std::string& title, int width, int height)
{
	window = SDL_CreateWindow(title.c_str(), 0, 0, width, height, 0);
	if (!window)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_renderer)
	{
		std::cerr << "SDL error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Renderer::PresentCanvas(const Canvas& canvas)
{
	// Copy canvas texture to renderer
	SDL_RenderCopy(m_renderer, canvas.m_texture, nullptr, nullptr);

	// Present renderer to the screen
	SDL_RenderPresent(m_renderer);
}
