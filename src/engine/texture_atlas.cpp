#include "texture_atlas.h"

// texture atlas region definitions
const SDL_Rect textureRegions[51] =
{
	SDL_Rect { 64, 64, 32, 32 },
	SDL_Rect { 64, 32, 32, 32 },
	SDL_Rect { 0, 0, 32, 32 },
	SDL_Rect { 64, 0, 32, 32 },
	SDL_Rect { 0, 32, 32, 32 },
	SDL_Rect { 0, 64, 32, 32 },
	SDL_Rect { 128, 0, 72, 112 },
	SDL_Rect { 128, 112, 120, 100 },
	SDL_Rect { 128, 216, 44, 36 },
	SDL_Rect { 108, 217, 36, 60 },
	SDL_Rect { 220, 0, 32, 32 },
	SDL_Rect { 220, 32, 32, 32 },
	SDL_Rect { 220, 64, 32, 32 },
	// civilian idling
	SDL_Rect { 416, 36, 34, 34 },
	SDL_Rect { 416, 72, 34, 34 },
	SDL_Rect { 416, 108, 34, 34 },
	SDL_Rect { 416, 146, 34, 34 },
	// civilian walking
	SDL_Rect { 416, 36, 103, 34 },
	SDL_Rect { 416, 72, 102, 34 },
	SDL_Rect { 416, 108, 100, 36 },
	SDL_Rect { 416, 146, 99, 34 },
	// civilian running
	SDL_Rect { 416, 36, 103, 34 },
	SDL_Rect { 416, 72, 102, 34 },
	SDL_Rect { 416, 108, 100, 36 },
	SDL_Rect { 416, 146, 99, 34 },
	// player idling
	SDL_Rect { 416, 408, 52, 59 },
	SDL_Rect { 416, 330, 52, 59 },
	SDL_Rect { 416, 258, 52, 59 },
	SDL_Rect { 416, 183, 52, 59 },
	// player walking
	SDL_Rect { 416, 408, 197, 59 },
	SDL_Rect { 416, 330, 197, 59 },
	SDL_Rect { 416, 258, 197, 59 },
	SDL_Rect { 416, 183, 197, 59 },
	// player running
	SDL_Rect { 416, 408, 197, 59 },
	SDL_Rect { 416, 330, 197, 59 },
	SDL_Rect { 416, 258, 197, 59 },
	SDL_Rect { 416, 183, 197, 59 },
	// objects
	SDL_Rect { 284, 0, 26, 19 },
	SDL_Rect { 284, 21, 19, 15 },
	SDL_Rect { 284, 38, 25, 14 },
	SDL_Rect { 284, 53, 16, 21 },
	SDL_Rect { 284, 76, 32, 32 },
	SDL_Rect { 284, 108, 32, 32 },
	SDL_Rect { 284, 141, 32, 32 },
	SDL_Rect { 284, 143, 20, 10 },
	SDL_Rect { 284, 156, 11, 14 },
	SDL_Rect { 284, 156, 11, 14 },
	SDL_Rect { 284, 156, 11, 14 },
	SDL_Rect { 284, 173, 25, 21 },
	SDL_Rect { 284, 197, 69, 33 },
	SDL_Rect { 284, 231, 23, 11 }
};

const TextureId ANIM_NONE_FRAMES[] = {};
// TODO: USE ACTUAL TEXTURES
const TextureId ANIM_GREEN_POTION_BUFF_FRAMES[] = {
	TextureId::TILE_GRASS,
	TextureId::TILE_BROWN_BRICK,
	TextureId::TILE_DARK_BRICK,
	TextureId::TILE_WHITE_BRICK
};

// const TextureId ANIM_PLAYER_WALK_RIGHT_FRAMES[] =
// {
// 	TextureId::PLAYER_WALK_RIGHT,
// 	TextureId::PLAYER_WALK_RIGHT, // TODO: JUST USE SPRITSHEETS?
// 	TextureId::PLAYER_WALK_RIGHT,
// 	TextureId::PLAYER_WALK_RIGHT
// }

const TextureId *animationFrames[] =
{
	ANIM_NONE_FRAMES,
	ANIM_GREEN_POTION_BUFF_FRAMES
};

const int animationFrameCounts[] =
{
	0,
	sizeof(animationFrames[1]) / sizeof(TextureId)
};

TextureAtlas::TextureAtlas(SDL_Texture* atlasImg)
{
	this->atlasImg = atlasImg;
}

int TextureAtlas::getWidth(TextureId textureId)
{
	return textureRegions[static_cast<int>(textureId)].w;
}

int TextureAtlas::getHeight(TextureId textureId)
{
	return textureRegions[static_cast<int>(textureId)].h;
}

void TextureAtlas::drawImg(SDL_Renderer* renderer, TextureId textureId, float x,
	float y, bool useMapOffset)
{
	int texture_index = static_cast<int>(textureId);

	dest.x = useMapOffset ? x - mapOffsetX : x;
	dest.y = useMapOffset ? y - mapOffsetY : y;
	dest.w = textureRegions[texture_index].w;
	dest.h = textureRegions[texture_index].h;

	// draw from atlas
	SDL_RenderCopy(renderer, atlasImg, &textureRegions[texture_index], &dest);
}

void TextureAtlas::drawSubimg(SDL_Renderer* renderer, TextureId textureId, SDL_Rect src,
	float x, float y, bool useMapOffset)
{
	int texture_index = static_cast<int>(textureId);

	// adjust source coordinates to get coordinate in full atlas
	src.x = src.x + textureRegions[texture_index].x;
	src.y = src.y + textureRegions[texture_index].y;

	dest.x = useMapOffset ? x - mapOffsetX : x;
	dest.y = useMapOffset ? y - mapOffsetY : y;
	dest.w = src.w;
	dest.h = src.h;

	SDL_RenderCopy(renderer, atlasImg, &src, &dest);
}

void TextureAtlas::drawAnim(SDL_Renderer* renderer, SimpleAnimation* anim,
	bool useMapOffset)
{
	int frame_num = anim->elapsedTimeMs / ANIMATION_FRAME_DURATION;

	if (frame_num < animationFrameCounts[int(anim->animId)])
	{
		drawImg(renderer, animationFrames[int(anim->animId)][frame_num],
			useMapOffset ? anim->x - mapOffsetX : anim->x,
			useMapOffset ? anim->y - mapOffsetY : anim->y);
	}
	else
	{
		anim->finished = true; // TODO: SHOULD PROBABLY BE DONE IN THE ANIM CODE
	}
}
