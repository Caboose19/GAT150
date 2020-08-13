#pragma once
#include "Math/transform.h"
#include "Engine.h"
#include "Object.h"
#include <vector>
namespace nc
{
	class Component;
	class GameObject : public Object
	{
	public:
		// Inherited via Object
		virtual bool Create(void* data = nullptr) override;

		virtual void Destory() override;	

		void AddCompoent(Component* component);
		void RemoveCompoent(Component* component);
		void RemoveAllCompoents();

		void Update();
		void Draw();

		template <typename T>
		T* GetComponent()
		{
			T* result{ nullptr };
			for (auto component : m_components)
			{
				result = dynamic_cast<T*> (component);
				if (result) break;
			}
			return result;
		}

		friend class PhysicsComponent;
		friend class Component;
	public:
		Transform m_transform;
		Engine* m_engine;
	protected:
		std::vector<Component*> m_components;
	};
}