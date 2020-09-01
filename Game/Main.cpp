	#include "Components/SpriteAnimationComponent.h"
	#include "Components/PlayerComponent.h"
	#include "Objects/ObjectFactory.h"
	#include "Objects/GameObject.h"
	#include "Graphics/Texture.h"
	#include "Components/Enemy.h"
	#include "Objects/Scene.h"
	#include"Core/Factory.h"
	#include "Core/Json.h"
	#include "Math/Math.h"
	#include "Tilemap.h"
	#include "Engine.h"
	#include "pch.h"
#include <Math\Random.h>

nc::Engine engine;
nc::GameObject player;
nc::Scene scene;
nc::SpriteAnimationComponent spriteAni;
//nc::Factory<nc::Object, std::string> ObjectFactory;

//void GameEvent()
//{
//
//}

int main(int, char**)
	{

		engine.Startup();
		
	
		
		//startup code


		nc::ObjectFactory::Instance().Inistialize();
		nc::ObjectFactory::Instance().Register("PlayerComponent", new nc::Creator<nc::PlayerComponent, nc::Object> );
		nc::ObjectFactory::Instance().Register("EnemyComponent", new nc::Creator<nc::EnemyComponent, nc::Object> );

		//nc::EventManager::Instance().Subscribe("PlayerDead", &GameEvent);

		rapidjson::Document document;
		nc::json::Load("scene.txt", document);
		scene.Create(&engine);
		scene.Read(document);

		nc::TileMap tileMap;
		nc::json::Load("tileMap.txt", document);
		tileMap.Read(document);
		tileMap.Create(&scene);



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
			
			engine.Update();
			scene.Update();
			
			//player->Update();

			if (engine.GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystems::eButtonSate::HELD)
			{
				return  quit;
			}

			//draw
			engine.GetSystem<nc::Renderer>()->BeginFrame();
			
			scene.Draw();
		
			engine.GetSystem<nc::Renderer>()->EndFrame();

			
		}
		scene.Destory();
		engine.Shutdown();
		return 0;
	}

