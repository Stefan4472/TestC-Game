#include "item_drop.h"

ItemDrop::ItemDrop(Item* item, float x, float y) // TODO: GET PRECISE WIDTH AND HEIGHT FROM SOMEWHERE (INSTEAD OF USING DEFAULT 32 FOR POSITION W/H)
{
	items = new ItemStack(item);
	setPosition(x, y);
}

ItemDrop::ItemDrop(ItemStack* itemStack, float x, float y)
{
	items = itemStack;
	setPosition(x, y);
}
		
ItemDrop::ItemDrop(int itemId, int quantity, float x, float y)
{
	items = new ItemStack(itemId, quantity);
	setPosition(x, y);
}

void ItemDrop::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

ItemStack* ItemDrop::getItems()
{
	return items;
}

void ItemStack::drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas, int offsetX, int offsetY)
{
	textureAtlas->draw(renderer, textureId, position.x - offsetX, position.y - offsetY);
}