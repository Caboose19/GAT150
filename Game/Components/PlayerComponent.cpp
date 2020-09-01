#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "pch.h"
#include <Components\RigidBodyComponent.h>
#include "Components/AudioComponent.h"
#include "Components/SpriteComponent.h"
#include "Core/EventManager.h"
namespace nc
{
	bool nc::PlayerComponent::Create(void* data)
	{

		m_owner = static_cast<GameObject*>(data);
	
		EventManager::Instance().Subscribe("CollisionEnter",std::bind(&PlayerComponent::CollisionEvent,this,std::placeholders::_1),m_owner);
		EventManager::Instance().Subscribe("CollisionExit",std::bind(&PlayerComponent::CollisionExit,this,std::placeholders::_1),m_owner);

		return true;
	}

	void nc::PlayerComponent::Destory()
	{
	}

	void nc::PlayerComponent::Update()
	{

		auto contacts = m_owner->GetContactsWithTag("Floor");
		bool onGround = !contacts.empty();

		nc::Vector2 force{ 0,0 };
		
		if (m_owner->m_engine->GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystems::eButtonSate::HELD)
		{
			force.x = -200;
			//m_owner->m_transform.angle = m_owner->m_transform.angle - 2000.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (m_owner->m_engine->GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystems::eButtonSate::HELD)
		{
			force.x = 200;
			//m_owner->m_transform.angle = m_owner->m_transform.angle + 20000.0f * m_owner->m_engine->GetTimer().DeltaTime();
		}
		if (onGround && m_owner->m_engine->GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystems::eButtonSate::PRESSED)
		{
			force.y = -1500;
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			if (audioComponent)
			{
				audioComponent->Play();
			}

		}
		
		

		
		RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
		if (component)
		{
			component->ApplyForce(force);

			Vector2 velocity = component->GetVelocity();

			SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
			if (velocity.x <= -0.5f) spriteComponent->Flip();
			if (velocity.x >= 0.5f) spriteComponent->Flip(false);
		}

		auto coinContacts = m_owner->GetContactsWithTag("Coin");
		for (GameObject* contact : coinContacts)
		{
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
		}

		auto EnemyContacts = m_owner->GetContactsWithTag("Enemy");
		for (GameObject* contact : EnemyContacts)
		{
			contact->m_flags[GameObject::eFlags::DESTROY] = true;
		}

	
	}

	void nc::PlayerComponent::CollisionEvent(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);
		std::cout << "collision enter: " <<gameObject->m_name<< std::endl;

		if (gameObject->m_tag == "Enemy")
		{
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			audioComponent->SetSoundName("grunt.wav");
			audioComponent->Play();

			gameObject->m_flags[GameObject::eFlags::DESTROY] = true;


		}

		if (gameObject->m_tag == "Coin")
		{
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			audioComponent->SetSoundName("Coin.wav");
			audioComponent->Play();

			gameObject->m_flags[GameObject::eFlags::DESTROY] = true;
		}
		
	
	}

	void PlayerComponent::CollisionExit(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);
		std::cout << "collision exit: " << gameObject->m_name << std::endl;
	}

}
	

