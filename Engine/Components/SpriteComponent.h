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

		void Read(const rapidjson::Value& value);

	protected:
		class Texture* m_texture;
		std::string m_textureName;
		SDL_Rect m_rect;
	};
}