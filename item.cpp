#include "item.h"

Item::Item(int itemId)
{
	this->itemId = itemId;
}

int Item::getId()
{
	return itemId;
}

const char* Item::getName()
{
	return ITEM_NAMES[itemId].c_str();
}
		
const char* Item::getDescription() // TODO: PASS CONST STD::STRING&
{
	return ITEM_DESCRIPTIONS[itemId].c_str();
}

int Item::getStackSize()
{
	return ITEM_STACKSIZES[itemId];
}

int Item::getTextureId()
{
	return ITEM_TEXTURES[itemId];
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