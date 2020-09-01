#include "pch.h"
#include "Enemy.h"
#include "Objects/GameObject.h"
#include "Objects/Scene.h"
#include "Components/PhysicsComponent.h"


bool nc::EnemyComponent::Create(void* data)
{
	return m_owner = static_cast<GameObject*>(data);
}

void nc::EnemyComponent::Destory()
{
}

void nc::EnemyComponent::Update()
{
	GameObject* player = m_owner->m_scene->Find("Player");
	if (player)
	{
		Vector2 direction = player->m_transform.position - m_owner->m_transform.position; //target - source
		Vector2 force = direction.Noramlized() * 10.0f;

		PhysicsComponent* physicsComponent = m_owner->GetComponent<PhysicsComponent>();
		physicsComponent->ApplyForce(force);
	}
}
