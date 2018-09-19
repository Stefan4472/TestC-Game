#ifndef BULLET_H
#define BULLET_H

#include <stdexcept>
#include "texture_atlas.h"
#include "item.h"

// Item used as ammunition for guns. Has a specific type.
class Bullet : public Item
{
	public:
		Bullet(ItemType bulletType);
		void getAndClearSounds(vector<Sound*> sounds);
};
#endif
