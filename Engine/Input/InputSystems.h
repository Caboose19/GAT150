#pragma once
#include "Core/System.h"
#include <SDL_stdinc.h>
namespace nc
{
	class InputSystems : public System
	{
	public:
		enum class eButtonSate
		{
			IDLE,
			PRESSED,
			HELD,
			REALEASED
		};
		// Inherited via System
		virtual bool StartUp() override;

		virtual void ShutDown() override;

		virtual void Update() override;

		eButtonSate GetButtonState(int id);
		bool GetButtonDown(int id);
		bool GetPreviousButtonDown(int id);



		const Uint8* SDL_GetKeyboardSate(int* numkeys);
		
	protected:
		Uint8* m_keystate;
		Uint8* m_prevKeystate;
		int m_numKeys;

	};
}