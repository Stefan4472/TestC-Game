#include "sword.h"

Sword::Sword() : Item(ItemType::SWORD)
{
	damage = 10;
}

void Sword::use(Sprite* actor) // TODO: REFACTORING, ADDITIONS, CLEAN UP
{
	this->actor = actor;
	swingDirection = actor->facingDir;
	SDL_Point handPos = actor->getRightHandPosition();
	SDL_Rect position = SDL_Rect { 0, 0, 32, 32 };
	// set position pased on handPosition and direction
	switch (actor->facingDir)
	{
		case Direction::RIGHT:		 // todo: this will require tweaking
			position.x = handPos.x;
			position.y = handPos.y - 16;
			break;

		case Direction::LEFT:
			position.x = handPos.x - 32;
			position.y = handPos.y - 16;
			break;

		case Direction::UP:
			position.x = handPos.x - 16;
			position.y = handPos.y - 32;
			break;

		case Direction::DOWN:
			position.x = handPos.x - 16;
			position.y = handPos.y;
			break;
	}
	lastAttack = new SwordSwing(position, actor);
}

Attack* Sword::getAttack()
{
	Attack* copy = lastAttack;
	lastAttack = NULL;
	return copy;
}

void Sword::getAndClearSounds(vector<Sound*> sounds)
{
	return;
}
