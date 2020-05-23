#include "TextureLoader.h"
#include "Consts.h"
#include "Log.h"

sf::Texture lbe::TextureLoader::DiamondHuntIcon;

lbe::TextureLoader::TextureLoader()
{
}


lbe::TextureLoader::~TextureLoader()
{
}

void lbe::TextureLoader::InitTextures()
{
	if (!DiamondHuntIcon.loadFromFile(lbe::DIAMONDHUNT_ICON))
	{
		LBE_WARN("Could not load texture file from {0}", lbe::DIAMONDHUNT_ICON.toAnsiString());
	}
}
