#include "pch.h"
#include "Renderer.h"

bool nc::Renderer::StartUp()
{
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	
	return true;
}

void nc::Renderer::ShutDown()
{
	IMG_Quit();
}

void nc::Renderer::Update()
{
}

bool nc::Renderer::Create(const std::string& name, int width, int height)
{
	 m_window = SDL_CreateWindow(name.c_str(), 100, 100, 1000, 600, SDL_WINDOW_SHOWN);

	if (m_window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

	if (m_renderer == nullptr)
	{
		std::cout << "Error:" << SDL_GetError() << std::endl;
	
		return false;
	}
	return true;
}

void nc::Renderer::BeginFrame()
{
	SDL_RenderClear(m_renderer);//begin of frame
}

void nc::Renderer::EndFrame()
{
	SDL_RenderPresent(m_renderer);//end of frame
}
