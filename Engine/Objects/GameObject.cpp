#include "pch.h"
#include "GameObject.h"
#include "Components/Component.h"
#include "Components/Render.h"
#include "Scene.h"
#include "ObjectFactory.h"
namespace nc 
{

	GameObject::GameObject(const GameObject& other)
	{
		m_name = other.m_name;
		m_tag = other.m_tag;
		m_lifetime = other.m_lifetime;

		m_flags = other.m_flags;

		m_transform = other.m_transform;
		m_engine = other.m_engine;

		for (Component* component : other.m_components)
		{
			Component* clone = dynamic_cast<Component*>(component->Clone());
			clone->m_owner = this;
			AddCompoent(clone);
		}
	}


	bool GameObject::Create(void* data)
	{
		return m_engine = static_cast<Engine*>(data);
		 
	}
	void GameObject::Destory()
	{
		RemoveAllCompoents();
	}

	void GameObject::Read(const rapidjson::Value& value)
	{
		json::Get(value, "name", m_name);
		json::Get(value, "tag", m_tag);
		json::Get(value, "lifetime", m_lifetime);

		bool transient = m_flags[eFlags::TRANSIENT];
		json::Get(value, "transient", transient);
		m_flags[eFlags::TRANSIENT] = transient;


		nc::json::Get(value, "position", m_transform.position);
		nc::json::Get(value, "scale", m_transform.scale);
		nc::json::Get(value, "angle", m_transform.angle);

		if (value.HasMember("Components"))
		{
			const rapidjson::Value& componentsValue = value["Components"];
			if (componentsValue.IsArray())
			{
				ReadComponents(componentsValue);
			}

		}

	}

	void GameObject::ReadComponents(const rapidjson::Value& value)
	{
		for (rapidjson::SizeType i = 0; i < value.Size(); i++)
		{
			const rapidjson::Value& componentValue = value[i];
			if (componentValue.IsObject())
			{
				std::string typeName;
				json::Get(componentValue, "type", typeName);

				Component* component = ObjectFactory::Instance().Create<Component>(typeName);
				
					if (component)
					{
						component->Create(this);
						component->Read(componentValue);
						GameObject::AddCompoent(component);
					}
			}
		}

	}


	void GameObject::Update()
	{
		for (auto component : m_components)
		{
			component->Update();
		}

		if (m_flags[eFlags::TRANSIENT])
		{
			m_lifetime = m_lifetime - m_engine->GetTimer().DeltaTime();
			m_flags[eFlags::DESTROY] = (m_lifetime <= 0);
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

	void GameObject::BeginContact(GameObject* other)
	{
		m_contacts.push_back(other);
	}

	void GameObject::EndContact(GameObject* other)
	{
		m_contacts.remove(other);
	}

	std::vector<GameObject*> GameObject::GetContactsWithTag(const std::string& tag)
	{
		std::vector<GameObject*> contacts;

		for (auto contact : m_contacts)
		{
			if (contact->m_tag == tag)
			{
				contacts.push_back(contact);
			}
		}
		return contacts;
	}

	void GameObject::AddCompoent(Component* component)
	{
		
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