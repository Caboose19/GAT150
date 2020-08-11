#pragma once
#include "Component.h"
namespace nc
{
	class Render : public  Component
	{
	public:
		virtual void Draw() = 0;
	};
}