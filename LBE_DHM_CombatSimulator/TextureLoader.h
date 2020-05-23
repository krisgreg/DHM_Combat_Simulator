#pragma once
#include <SFML/Graphics.hpp>

namespace lbe
{
	class TextureLoader
	{
	public:
		static sf::Texture DiamondHuntIcon;

		TextureLoader();
		~TextureLoader();

		static void InitTextures();
	};
}