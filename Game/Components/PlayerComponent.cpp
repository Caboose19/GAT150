#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "pch.h"
#include <Components\RigidBodyComponent.h>

bool nc::PlayerComponent::Create(void* data)
{
	return m_owner = static_cast<GameObject*>(data);
	
}

void nc::PlayerComponent::Destory()
{
}

void nc::PlayerComponent::Update()
{
	nc::Vector2 force{ 0,0 };

	if (m_owner->m_engine->GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystems::eButtonSate::HELD)
	{
		force.x = -200000;
		//m_owner->m_transform.angle = m_owner->m_transform.angle - 2000.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystems::eButtonSate::HELD)
	{
		force.x = 200000;
		//m_owner->m_transform.angle = m_owner->m_transform.angle + 20000.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystems::eButtonSate::PRESSED)
	{
		force.y = -200000;
	}

	/*if (m_owner->m_engine->GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystems::eButtonSate::HELD)
	{
		force = nc::Vector2::Forward * 1000.0f;
	}*/
	//force = nc::Vector2::Rotate(force, nc::DegreesToRadians(m_owner->m_transform.angle));

	RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
	if (component)
	{
		component->ApplyForce(force);
	}
}
