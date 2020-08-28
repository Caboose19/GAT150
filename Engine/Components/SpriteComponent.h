#pragma once
#include "Components/Render.h"

namespace nc
{
	class SpriteComponent : public Render
	{
	public:


		// Inherited via Render
		virtual bool Create(void* data = nullptr) override;

		virtual Object* Clone() override { return new SpriteComponent{ *this }; }

		virtual void Destory() override;

		virtual void Update() override;

		virtual void Draw() override;

		void Read(const rapidjson::Value& value);

	protected:
		class Texture* m_texture;
		std::string m_textureName;
		Vector2 m_origin{0,0};
		SDL_Rect m_rect{0,0,0,0};
	};
}