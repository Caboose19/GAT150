#pragma once
#include <fmod.hpp>
#include "Core/System.h"
namespace nc
{
	class AudioSystem : public System
	{
		virtual bool StartUp() override;
		virtual void ShutDown() override;
		virtual void Update() override;

		friend class Sound;

	protected:
		FMOD::System* m_system{ nullptr };

	};
}
