#include "bullet.h"

Bullet::Bullet(ItemType itemType) : Item(itemType)
{
	if (itemType != ItemType::PISTOL_AMMO && itemType != ItemType::SHOTGUN_AMMO &&
		itemType != ItemType::RIFLE_AMMO)
	{
		throw runtime_error("Invalid Id for Bullet given");
	}
}

void Bullet::getAndClearSounds(vector<Sound*> sounds)
{
	return;
}
