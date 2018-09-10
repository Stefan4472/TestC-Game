#include "item_drop.h"

ItemDrop::ItemDrop(Item* item, float x, float y)
{
	printf("Creating ItemDrop from %s at %f, %f...", item->name.c_str(), x, y);
	items = new ItemStack(item);

	hitbox.w = HITBOX_WIDTH;
	hitbox.h = HITBOX_HEIGHT;

	setPosition(x, y);
	printf("Done\n");
}

ItemDrop::ItemDrop(ItemStack* itemStack, float x, float y)
{
	printf("Creating ItemDrop from stack %s with size %d at %f, %f...",
		itemStack->peekNext()->name.c_str(), itemStack->size(), x, y);
	items = itemStack;

	hitbox.w = HITBOX_WIDTH;
	hitbox.h = HITBOX_HEIGHT;

	setPosition(x, y);
	printf("Done\n");
}

void ItemDrop::setPosition(float x, float y)
{
	hitbox.x = x;
	hitbox.y = y;
}

ItemStack* ItemDrop::getStack()
{
	return items;
}

// TODO: CLEAN UP
void ItemDrop::drawToMap(SDL_Renderer* renderer, TextureAtlas* textureAtlas)
{
	textureAtlas->draw(renderer, getTextureId(items->itemId), position.x, position.y);
}
