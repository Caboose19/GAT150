#pragma once
#include "matrix33.h"
namespace nc
{

	struct Transform
	{
	public:
		Vector2 position;
		float scale;
		float angle;

		Matrix33 matrix;

		Transform() : position{ 0,0 }, scale{ 1 }, angle{ 0 }{}
		Transform(const Vector2& position, float scale, float angle) : position{ position }, scale{ scale }, angle{ angle }{}

		void Update();
		void Update(const Matrix33& mx);

		friend std::istream& operator >> (std::istream& stream, Transform& transform);
	};

}