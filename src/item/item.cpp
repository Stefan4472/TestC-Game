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

void Item::update(int ms)
{
	return;	
}

void Item::use(const Sprite* actor)
{
	return;	
}

SpriteAction* Item::getAction()
{
	return NULL;
}

SpriteAction* Item::getBuff()
{
	return NULL;
}

Attack* Item::getAttack()
{
	return NULL;
}

int getStackSize(int itemId) 
{
	return ITEM_STACKSIZES[itemId];	
}

int getTextureId(int itemId)
{
	return ITEM_TEXTURES[itemId];	
}