#pragma once
#include "Components/Render.h"

namespace nc
{
	class SpriteComponent : public Render
	{
	public:


		// Inherited via Render
		virtual bool Create(void* data = nullptr) override;

		virtual void Destory() override;

		virtual void Update() override;

		virtual void Draw() override;

	protected:
		class Texture* m_texture;
	};
}