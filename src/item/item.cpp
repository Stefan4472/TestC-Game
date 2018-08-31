#include "item.h"

Item::Item(int itemId)
{
	printf("Creating Item with id %d...", itemId);
	this->itemId = itemId;
	name = ITEM_NAMES[itemId];
	description = ITEM_DESCRIPTIONS[itemId];
	stackSize = ITEM_STACKSIZES[itemId];
	textureId = ITEM_TEXTURES[itemId];
	ammunitionId = ITEM_AMMUNITIONS[itemId];
	printf("Done\n");
}

bool Item::load(Item* item)
{
	return false;
}

void Item::use(const Sprite* actor)
{
	return;
}

void Item::update(int ms)
{
	return;
}

SpriteAction* Item::getAction()
{
	return NULL;
}

SpriteBuff* Item::getBuff()
{
	return NULL;
}

Attack* Item::getAttack()
{
	return NULL;
}

int Item::getStackSize(int itemId)
{
	if (itemId < 1 || itemId >= ItemType::NUM_ITEMS)
	{
		throw runtime_error("Invalid itemId");
	}
	return ITEM_STACKSIZES[itemId];
}

TextureId Item::getTextureId(int itemId)
{
	if (itemId < 1 || itemId >= ItemType::NUM_ITEMS)
	{
		throw runtime_error("Invalid itemId");
	}
	return ITEM_TEXTURES[itemId];
}
