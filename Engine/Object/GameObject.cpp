#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/Render.h"

namespace nc 
{
	bool GameObject::Create(void* data)
	{
		return false;
	}
	void GameObject::Destory()
	{
	}


	void GameObject::Update()
	{
		for (auto component : m_components)
		{
			component->Update();
		}
	}

	void GameObject::Draw()
	{
		
		Render* component = GetComponent<Render>();

		if (component)
		{
			component->Draw();
		}
		
	}

	
	void GameObject::AddCompoent(Component* component)
	{
		component->m_owner = this;
		m_components.push_back(component);
	}
	
	void GameObject::RemoveCompoent(Component* component)
	{
		auto iter = std::find(m_components.begin(), m_components.end(), component);
		if (iter != m_components.end())
		{
			(*iter)->Destory();
			delete (*iter);
		}
	}
	
	void GameObject::RemoveAllCompoents()
	{
		for (auto component : m_components)
		{
			component->Destory();
			delete component;
		}
		m_components.clear();
	}

}