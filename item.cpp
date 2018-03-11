#include "item.h"

void Item::init(TextureAtlas* textureAtlas, int itemType)
{
	this->textureAtlas = textureAtlas;
	this->textureId = ITEM_IMAGES[itemType];
	this->itemType = itemType;
	name = ITEM_NAMES[itemType];
	description = ITEM_NAMES[itemType];
	stackSize = ITEM_STACKSIZES[itemType];
}

Item::Item(int itemId)
{
	this->itemId = itemId;
}

const char* Item::getName() 
{
	return name.c_str();	
}

bool Item::load(Item* item)
{
	return false;
}

void Item::update(int ms)
{
	return;	
}

Action* Item::getAction()
{
	return NULL;
}

Action* Item::getBuff()
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