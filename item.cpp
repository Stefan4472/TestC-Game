#include "item.h"

Item::Item(int itemId)
{
	this->itemId = itemId;
	name = ITEM_NAMES[itemId].c_str();
	description = ITEM_DESCRIPTIONS[itemId].c_str();
	stackSize = ITEM_STACKSIZES[itemId];
	textureId = ITEM_TEXTURES[itemId];
	ammunitionId = ITEM_AMMUNITIONS[itemId];
}

/*const char* Item::getName()
{
	return ITEM_NAMES[itemId].c_str();
}
		
const char* Item::getDescription() // TODO: PASS CONST STD::STRING&
{
	return ITEM_DESCRIPTIONS[itemId].c_str();
}*/

bool Item::load(Item* item)
{
	return false;
}

void Item::update(int ms)
{
	return;	
}

void use(const Sprite* actor)
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

int getTextureId(int itemId)
{
	return ITEM_TEXTURES[itemId];	
}