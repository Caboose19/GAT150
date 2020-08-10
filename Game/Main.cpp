	#include "Resources/ResourceManager.h"
	#include "Input/InputSystems.h"
	#include "Graphics/Renderer.h"
	#include "Graphics/Texture.h"
	#include "Core/Timer.h"
	#include "pch.h"

nc::ResourceManager resourcemanager;
nc::Renderer renderer;
nc::FrameTimer ftimer;
nc::InputSystems inputSystems;

int main(int, char**)
	{
	

		//profile
	//	for (size_t i = 0; i < 100000; i++)
	//	{
	//		std::sqrt(rand() % 100);
	//	}
	//	std::cout << timer.ElapsedSeconds() << std::endl;

		inputSystems.StartUp();
		renderer.StartUp();
		renderer.Create("GAT150", 800, 600);
		//texture
		nc::Texture* car = resourcemanager.Get<nc::Texture>("cars.png",&renderer);
		nc::Texture* background = resourcemanager.Get<nc::Texture>("background.png",&renderer);
		
		float angle{ 0 };
		nc::Vector2 position{ 400,300 };

		SDL_Event event;
		bool quit = false;
		while (!quit)
		{
			SDL_PollEvent(&event);
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			}
			//update
			inputSystems.Update();
			ftimer.Tick();

			if (inputSystems.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystems::eButtonSate::HELD)
			{
				position.x = position.x - 1.0f;
			}
			if (inputSystems.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystems::eButtonSate::HELD)
			{
				position.x = position.x + 1.0f;
			}


			renderer.BeginFrame();
			
			angle = angle + 180 * ftimer.DeltaTime();
			background->Draw({ 0,0 }, { 1.0f,1.0f },0);
			car->Draw({0,16,64,144}, {position}, { 1.0f,1.0f }, 0);

			renderer.EndFrame();

			
		}
		
		inputSystems.ShutDown();
		renderer.ShutDown();
		SDL_Quit();
		return 0;
	}
