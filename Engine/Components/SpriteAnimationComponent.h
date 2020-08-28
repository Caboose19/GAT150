#pragma once
#include "SpriteComponent.h"


namespace nc
{
	class SpriteAnimationComponent : public SpriteComponent
	{
	public:
		virtual bool Create(void* data = nullptr) override;

		virtual Object* Clone() override { return new SpriteAnimationComponent{ *this }; }

		virtual void Destory() override;

		virtual void Update() override;


		void Read(const rapidjson::Value& value);

	protected:
		int m_frame{ 0 };
		float m_frametimer{0};
		float m_framerate{ 0 };

		int m_numX{ 0 };
		int m_numY{ 0 };
		int m_numFrames{ 0 };
		int m_fps{ 0 };

		
	};
}