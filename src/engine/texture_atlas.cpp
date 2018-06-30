#include "texture_atlas.h"

TextureAtlas::TextureAtlas(SDL_Texture* atlas)
{
	this->atlas = atlas;
}

void TextureAtlas::draw(SDL_Renderer* renderer, int textureId, float x, float y)
{
	dest.x = x;
	dest.y = y;
	dest.w = textureRegions[textureId].w;
	dest.h = textureRegions[textureId].h;
	// draw from atlas 
	SDL_RenderCopy(renderer, atlas, &textureRegions[textureId], &dest);
}

void TextureAtlas::drawSubimg(SDL_Renderer* renderer, int textureId, SDL_Rect src, float x, float y)
{
	// adjust source coordinates to get coordinate in full atlas
	src.x = src.x + textureRegions[textureId].x;
	src.y = src.y + textureRegions[textureId].y;
	dest.x = x;
	dest.y = y;
	dest.w = src.w;
	dest.h = src.h;
	SDL_RenderCopy(renderer, atlas, &src, &dest);
}

int TextureAtlas::getWidth(int textureId) 
{
	return textureRegions[textureId].w;
}

int TextureAtlas::getHeight(int textureId)
{
	return textureRegions[textureId].h;
}