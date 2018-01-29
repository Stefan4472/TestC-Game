#include "civilian_sprite_controller.h"

CivilianSpriteController::CivilianSpriteController(CivilianSprite* sprite) : SpriteController(sprite)
{
	currAction = new WanderAction(ACTION_LOOPING, 10, 400, 100);
	inventory = new Inventory(sprite, 5);	
}

void CivilianSpriteController::update(int ms)
{
	currAction->apply(sprite, ms);
}

void CivilianSpriteController::handleAttacked(Attack* attack)
{
	printf("Civilian Attacked!!\n");
	
	// replace current action with knockback in the direction of the attack
	//delete currAction;
	//currAction = new KnockbackAction(attack->dir);
	
	// handle loss of hp and show healthbar
	sprite->loseHealth(attack->damage);
	sprite->healthbar->changeHealth(-attack->damage);
	//sprite->showHealthbar();
	
	// add sound
	sounds.push_back(SOUND_2);
}

void CivilianSpriteController::handleSoundHeard(Sound* sound)
{
	printf("Sprite %d heard sound %d\n", sprite, sound->soundId);
}

void CivilianSpriteController::handleSpriteSeen(Sprite* sprite)
{
	//printf("Sprite %d sees sprite %d\n", this, sprite);
}
