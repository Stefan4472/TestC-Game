#include "texture_atlas.h"

TextureAtlas::TextureAtlas(SDL_Surface* atlas)
{
	this->atlas = atlas;
}

void TextureAtlas::draw(SDL_Surface* screenSurface, int textureId, float x, float y)
{
	dest.x = x;
	dest.y = y;
	dest.w = textureRegions[textureId].w;
	dest.h = textureRegions[textureId].h;
	// draw from atlas 
	SDL_BlitSurface( atlas, &textureRegions[textureId], screenSurface, &dest );
}

int TextureAtlas::getWidth(int textureId) 
{
	return textureRegions[textureId].w;
}

int TextureAtlas::getHeight(int textureId)
{
	return textureRegions[textureId].h;
}