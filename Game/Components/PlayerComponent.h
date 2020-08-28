#pragma once
#include "Components/Component.h"

namespace nc
{
	class PlayerComponent : public Component
	{
	public:
		virtual bool Create(void* data = nullptr) override;
		virtual Object* Clone() override { return new PlayerComponent{ *this }; }
		virtual void Destory() override;
		virtual void Update() override;
	};
}