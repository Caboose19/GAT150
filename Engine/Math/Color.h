#pragma once
#include <windows.h>
#include <iostream>

namespace nc
{
	struct Color
	{
		float r;
		float g;
		float b;
		float a;


		Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 } {}
		Color(float r, float g, float b, float a = 1) : r{ r }, g{ g }, b{ b }, a{ a } {}


		float& operator [] (size_t index);
		//const float& operator[] const(size_t index);
		void Set(float r, float g, float b);

		Color operator + (const Color& c) const { return Color{ r + c.r, g + c.g , b + c.b}; }
		Color operator - (const Color& c) const { return Color{ r - c.r, g - c.g , b - c.b}; }
		Color operator * (const Color& c) const { return Color{ r * c.r, g * c.g , b * c.b}; }
		Color operator / (const Color& c) const { return Color{ r / c.r, g / c.g , b / c.b}; }

		Color operator + (float c) const { return Color{ r - c, g - c, b - c}; }
		Color operator - (float c) const { return Color{ r - c, g - c, b - c}; }
		Color operator * (float c) const { return Color{ r * c, g * c, b * c}; }
		Color operator / (float c) const { return Color{ r / c, g / c, b / c}; }

		Color& operator += (const Color& c) { r += c.r; g += c.g; b += c.b; return *this; }
		Color& operator -= (const Color& c) { r -= c.r; g -= c.g; b -= c.b; return *this; }
		Color& operator *= (const Color& c) { r *= c.r; g *= c.g; b *= c.b; return *this; }
		Color& operator /= (const Color& c) { r /= c.r; g /= c.g; b /= c.b; return *this; }

		Color& operator += (float c) { r += c; g += c; b += c; return *this; }
		Color& operator -= (float c) { r -= c; g -= c; b -= c; return *this; }
		Color& operator *= (float c) { r *= c; g *= c; b *= c; return *this; }
		Color& operator /= (float c) { r /= c; g /= c; b /= c; return *this; }


		friend std::istream& operator >> (std::istream& stream, Color& c);

		

		static const Color white;
		static const Color red;
		static const Color green;
		static const Color blue;

		SDL_Color  Pack888() const;
		operator SDL_Color() const { return Pack888(); }
	};
		
	
	inline SDL_Color Color::Pack888() const
		{

			SDL_Color color;
			BYTE _r = static_cast<BYTE>(r * 255.0f);
			BYTE _g = static_cast<BYTE>(g * 255.0f);
			BYTE _b = static_cast<BYTE>(b * 255.0f);
			BYTE _a = static_cast<BYTE>(b * 255.0f);

			return color;
	}


}