#include "pch.h"
#include "Engine.h"



bool nc::Engine::Startup()
{

	srand(static_cast<unsigned int>(time(nullptr)));

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{

		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_systems.push_back(new Renderer);
	m_systems.push_back(new InputSystems);
	m_systems.push_back(new ResourceManager);
	m_systems.push_back(new PhysicsSystem);
	m_systems.push_back(new AudioSystem);
	

	for (auto system : m_systems)
	{
		system->StartUp();
	}

	GetSystem<Renderer>()->Create("GAT150", 800, 600);

	return true;
}

void nc::Engine::Shutdown()
{
	for (auto system : m_systems)
	{
		system->ShutDown();
		delete system;
	}
	m_systems.clear();

	SDL_Quit();
}

void nc::Engine::Update()
{
	m_timer.Tick();
	for (auto system : m_systems)
	{
		system->Update();
	}
}
