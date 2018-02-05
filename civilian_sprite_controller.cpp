#include "civilian_sprite_controller.h"

CivilianSpriteController::CivilianSpriteController(CivilianSprite* sprite, PathFinder* pathFinder) : SpriteController(sprite)
{
	this->pathFinder = pathFinder;
	// default action is to wander
	actionStack.push(new WanderAction(pathFinder, ACTION_LOOPING, 10, 400, 100));
	inventory = new Inventory(sprite, 5);
	//inventory->addItem(new Sword(textureAtlas, 164, 200));
}

void CivilianSpriteController::update(int ms)
{
	SpriteController::update(ms);
	
	// switch to next action if top is finished
	if (!actionStack.top()->apply(sprite, ms))
	{
		delete actionStack.top();
		actionStack.pop();
		actionStack.top()->init(sprite);
	}
}

void CivilianSpriteController::handleAttacked(Attack* attack)
{
	printf("Civilian Attacked by %d!!\n", attack->attacker);
	
	// add action to follow attacker
	actionStack.push(new FollowAction(pathFinder, 10, attack->attacker)); // TODO: WON'T THIS RESULT IN A BUNCH OF REPEATING FOLLOW ACTIONS?
	
	// add action to knockback in the direction of the attack (happens first)
	actionStack.push(new KnockbackAction(attack->dir));
	
	// handle loss of hp and show healthbar
	sprite->loseHealth(attack->damage);
	sprite->healthbar->changeHealth(-attack->damage);
	sprite->showHealthbar();
	
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
