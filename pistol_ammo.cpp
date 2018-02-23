#include "pistol_ammo.h"

PistolAmmo::PistolAmmo(TextureAtlas* textureAtlas, float x, float y) : Item(textureAtlas, ITEM_BULLET, x, y)
{
	
}

void PistolAmmo::use(Sprite* actor, SDL_Point handPos, int useDir)
{
	return;
}