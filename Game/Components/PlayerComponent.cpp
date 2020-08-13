#include "PlayerComponent.h"
#include "Components/PhysicsComponent.h"
#include "pch.h"

bool nc::PlayerComponent::Create(void* data)
{
	return true;
}

void nc::PlayerComponent::Destory()
{
}

void nc::PlayerComponent::Update()
{

	if (m_owner->m_engine->GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystems::eButtonSate::HELD)
	{
		m_owner->m_transform.angle = m_owner->m_transform.angle - 90.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystems::eButtonSate::HELD)
	{
		m_owner->m_transform.angle = m_owner->m_transform.angle + 90.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}

	nc::Vector2 force{ 0,0 };

	if (m_owner->m_engine->GetSystem<nc::InputSystems>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystems::eButtonSate::HELD)
	{
		force = nc::Vector2::Forward * 1000.0f;
	}
	force = nc::Vector2::Rotate(force, nc::DegreesToRadians(m_owner->m_transform.angle));

	PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();

	if (component)
	{
		component->ApplyForce(force);
	}
}
