#ifndef pistol_ammo_h
#define pistol_ammo_h

#include "item.h"
#include "texture_atlas.h"

// Item used to fire a pistol.

class PistolAmmo : public Item
{
	public:
		PistolAmmo(TextureAtlas* textureAtlas, float x, float y);
		// doesn't do anything
		void use(Sprite* actor, SDL_Point handPos, int useDir);
};
#endif