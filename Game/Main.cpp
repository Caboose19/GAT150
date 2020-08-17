	#include "Components/PhysicsComponent.h"
	#include "Components/SpriteComponent.h"
	#include "Components/PlayerComponent.h"
	#include "Objects/GameObject.h"
	#include "Graphics/Texture.h"
	#include "Math/Math.h"
	#include "Core/Json.h"
	#include"Core/Factory.h"
	#include "Engine.h"
	#include "pch.h"

nc::Engine engine;
nc::GameObject player;
nc::Factory<nc::Object, std::string> ObjectFactory;

int main(int, char**)
	{
	
	rapidjson::Document document;
	


		engine.Startup();
		
		ObjectFactory.Register("GameObject", nc::Object::Instantiate<nc::GameObject>);
		ObjectFactory.Register("PhysicsComponent", nc::Object::Instantiate<nc::PhysicsComponent>);
		ObjectFactory.Register("SpriteComponent", nc::Object::Instantiate<nc::SpriteComponent>);
		ObjectFactory.Register("PlayerComponent", nc::Object::Instantiate<nc::PlayerComponent>);

		nc::GameObject* player = ObjectFactory.Create<nc::GameObject>("GameObject");

		player->Create(&engine);
		nc::json::Load("player.txt", document);
		player->Read(document);

		nc::Component* component; //= new nc::PhysicsComponent;
		component = ObjectFactory.Create<nc::Component>("PhysicsComponent");
		player->AddCompoent(component);
		component->Create();
		
		component = new nc::SpriteComponent;
		component = ObjectFactory.Create<nc::Component>("SpriteComponent");
		player->AddCompoent(component);
		nc::json::Load("sprite.txt", document);
		component->Read(document);
		component->Create();
		
		component = new nc::PlayerComponent;
		component = ObjectFactory.Create<nc::Component>("PlayerComponent");
		player->AddCompoent(component);
		component->Create();


		//texture
		nc::Texture* background = engine.GetSystem<nc::ResourceManager>()->Get<nc::Texture>("background.png",engine.GetSystem<nc::Renderer>());
		
		
		

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
			player->Update();


			if (engine.GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystems::eButtonSate::HELD)
			{
				return  quit;
			}

			//physics

			

			//draw
			engine.GetSystem<nc::Renderer>()->BeginFrame();
			
		
			background->Draw({ 0,0 }, { 1.0f,1.0f },0);
			//render sprite
			
			player->Draw();

			engine.GetSystem<nc::Renderer>()->EndFrame();

			
		}
		
		engine.Shutdown();
		return 0;
	}
/*
std::string str;
nc::json::Get(document, "string", str);
std::cout << str << std::endl;

bool b;
nc::json::Get(document, "bool", b);
std::cout << b << std::endl;

int i1;
nc::json::Get(document, "integer1", i1);
std::cout << i1 << std::endl;

int i2;
nc::json::Get(document, "integer2", i2);
std::cout << i2 << std::endl;

float f;
nc::json::Get(document, "float", f);
std::cout << f << std::endl;

nc::Vector2 v2;
nc::json::Get(document, "vector2", v2);
std::cout << v2 << std::endl;

nc::Color color;
nc::json::Get(document, "color", color);
std::cout << color << std::endl;
*/

