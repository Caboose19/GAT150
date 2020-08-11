#pragma once
#include "Math/Vector2.h"
#include "Component.h"
namespace nc
{
	class PhysicsComponent : public Component
	{
	public:
		
		virtual bool Create(void* data = nullptr) override;
		virtual void Destory() override;

		virtual void Update() override;

	protected:
		Vector2 m_velocity;
		Vector2 m_force;
		float m_drag{ 1 };

		// Inherited via Component
	};
}
