#include "item.h"

// TextureIds corresponding to ItemType enum
const TextureId ITEM_TEXTURES[NUM_ITEM_TYPES] =
{
	TextureId::TEXTURE_NONE,
	TextureId::BREAD_LOAF,
	TextureId::CHICKEN_LEG,
	TextureId::BEER_MUG,
	TextureId::POTION_GREEN,
	TextureId::SCROLL_1,
	TextureId::SWORD_1,
	TextureId::OBJECT_PISTOL_1,
	TextureId::TEXTURE_PISTOL_AMMO,
	TextureId::TEXTURE_SHOTGUN_AMMO,
	TextureId::TEXTURE_RIFLE_AMMO,
	TextureId::TEXTURE_SHOTGUN,
	TextureId::TEXTURE_TOMMYGUN
};

// names of items, corresponding to ItemType enum
const std::string ITEM_NAMES[NUM_ITEM_TYPES] =
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

// descriptions of items, corresponding to ItemType enum
const std::string ITEM_DESCRIPTIONS[NUM_ITEM_TYPES] =
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

// item stacksizes, corresponding to ItemType enum
const int ITEM_STACKSIZES[NUM_ITEM_TYPES] =
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

// item ammunitionTypes, corresponding to ItemType enum
const ItemType ITEM_AMMUNITIONS[NUM_ITEM_TYPES] =
{
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::PISTOL_AMMO,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::NONE,
	ItemType::SHOTGUN_AMMO,
	ItemType::RIFLE_AMMO
};

string Item::getName(ItemType itemType)
{
	return ITEM_NAMES[int(itemType)];
}

string Item::getDescription(ItemType itemType)
{
	return ITEM_DESCRIPTIONS[int(itemType)];
}

int Item::getStackSize(ItemType itemType)
{
	return ITEM_STACKSIZES[int(itemType)];
}

TextureId Item::getTextureId(ItemType itemType)
{
	return ITEM_TEXTURES[int(itemType)];
}

ItemType Item::getAmmunitionType(ItemType itemType)
{
	return ITEM_AMMUNITIONS[int(ItemType)];
}

Item::Item(ItemType itemType)
{
	printf("Creating Item with id %d...", int(itemType));
	this->itemType = itemType;
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
