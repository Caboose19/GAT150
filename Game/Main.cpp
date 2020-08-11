	#include "Resources/ResourceManager.h"
	#include "Input/InputSystems.h"
	#include "Graphics/Renderer.h"
	#include "Graphics/Texture.h"
	#include "Core/Timer.h"
	#include "Math/Math.h"
	#include "pch.h"

nc::ResourceManager resourcemanager;
nc::FrameTimer timer;
nc::InputSystems inputSystems;
nc::Renderer renderer;

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
		
		nc::Vector2 position{ 500,200 };
		nc::Vector2 velocity;
		float angle{ 0 };

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
			timer.Tick();


			if (inputSystems.GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystems::eButtonSate::HELD)
			{
				return  quit;
			}

			if (inputSystems.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystems::eButtonSate::HELD)
			{
				angle = angle - 90.0f * timer.DeltaTime();
			}
			if (inputSystems.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystems::eButtonSate::HELD)
			{
				angle = angle + 90.0f * timer.DeltaTime();
			}
			nc::Vector2 force{ 0,0 };
			if (inputSystems.GetButtonState(SDL_SCANCODE_W) == nc::InputSystems::eButtonSate::HELD)
			{
				force = nc::Vector2::Forward * 1000.0f;
			}
			force = nc::Vector2::Rotate(force, nc::DegreesToRadians(angle));
			//physics

			velocity = velocity + force * timer.DeltaTime();
			velocity = velocity * 0.98f;
			position = position + velocity * timer.DeltaTime();

			//draw
			renderer.BeginFrame();
			
		
			background->Draw({ 0,0 }, { 1.0f,1.0f },0);
			//render sprite
			car->Draw({120,30,70,90}, {position}, { 1.0f,1.0f }, angle);

			renderer.EndFrame();

			
		}
		
		inputSystems.ShutDown();
		renderer.ShutDown();
		SDL_Quit();
		return 0;
	}
