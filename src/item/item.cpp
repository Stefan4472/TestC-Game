#include "item.h"

// TextureIds corresponding to ItemType enum
const TextureId ITEM_TEXTURES[] =
{
	TextureId::TEXTURE_NONE,
	TextureId::BREAD_LOAF,
	TextureId::CHICKEN_LEG,
	TextureId::BEER_MUG,
	TextureId::POTION_GREEN,
	TextureId::SCROLL_1,
	TextureId::SWORD_1,
	TextureId::OBJECT_PISTOL_1,
	//PISTOL_BULLET,
	TextureId::TEXTURE_PISTOL_AMMO,
	TextureId::TEXTURE_SHOTGUN_AMMO,
	TextureId::TEXTURE_RIFLE_AMMO,
	TextureId::TEXTURE_SHOTGUN,
	TextureId::TEXTURE_TOMMYGUN
};

const std::string ITEM_NAMES[] =
{
	"The Null Item",
	"Bread Loaf",
	"Chicken Leg",
	"Beer Mug",
	"Green Potion",
	"Scroll",
	"Sword",
	"Pistol",
	"Pistol Bullet",
	"Shotgun Shell",
	"Rifle Bullet",
	"Double-Barelled Shotgun",
	"Tommy Gun"
};

const std::string ITEM_DESCRIPTIONS[] =
{
	"Nothing. This is probably a bug",
	"A Loaf of Bread",
	"Chicken Leg. Very tasty",
	"A big mug o' beer",
	"Not sure what it does, but it's green",
	"Some weird crinkled piece of paper with writing on it",
	"Sharp Steel",
	"Fancy-looking pistol. Bang bang!",
	"Small, metallic cylinder. For pistol use only!",
	"Shell for a shotgun",
	"Rifle bullet",
	"Nasty Double-Barelled Shotgun. Might be from the Civil War",
	"Not your grandma's Tommy Gun"
};

const int ITEM_STACKSIZES[] =
{
	1,
	16,
	16,
	4,
	4,
	1,
	1,
	1,
	48,
	24,
	32,
	1,
	1
};

Item::Item(int itemId)
{
	printf("Creating Item with id %d...", itemId);
	this->itemId = ItemType(itemId);
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

void Item::getAndClearSounds(vector<Sound*> sounds)
{
		return;
}

int Item::getStackSize(int itemId)  // TODO: TAKE iTEMtYPE AS ARG
{
	if (itemId < 1 || itemId >= int(ItemType::NUM_ITEMS))
	{
		throw runtime_error("Invalid itemId");
	}
	return ITEM_STACKSIZES[itemId];
}

TextureId Item::getTextureId(int itemId)
{
	if (itemId < 1 || itemId >= int(ItemType::NUM_ITEMS))
	{
		throw runtime_error("Invalid itemId");
	}
	return ITEM_TEXTURES[itemId];
}
