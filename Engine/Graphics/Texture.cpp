#include "pch.h"
#include "Texture.h"


namespace nc {
	bool nc::Texutre::Create(const std::string& name,SDL_Renderer* renderer)
	{
		m_renderer = renderer;

		SDL_Surface* surface = IMG_Load(name.c_str());
		if (surface == nullptr)
		{
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		SDL_FreeSurface(surface);
		if (m_texture == nullptr)
		{
			return false;
		}
		return true;
	}

	void nc::Texutre::Destory()
	{
		delete m_texture;
	}

	void nc::Texutre::Draw(const Vector2& position, const Vector2& scale, float angle)
	{
		Vector2 size = GetSize();
		size = size * scale;

		SDL_Rect rect;
		rect.x = static_cast<int>(position.x);
		rect.y = static_cast<int>(position.y);
		rect.w = static_cast<int>(size.x);
		rect.h = static_cast<int>(size.y);
		SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &rect,angle,nullptr,SDL_FLIP_NONE);
	}

	Vector2 nc::Texutre::GetSize()
	{
		int w, h;
		SDL_QueryTexture(m_texture, NULL, NULL, &w,&h);
		return Vector2(w,h);
	}
}