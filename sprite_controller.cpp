#include "sprite_controller.h"

SpriteController::SpriteController(Sprite* sprite)
{
	this->sprite = sprite;
}

/*void SpriteController::update(int ms)
{
	currAction->apply(sprite, ms);
}

void SpriteController::handleAttacked(Attack* attack)
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
	sprite->sounds.push_back(SOUND_2);
}

void SpriteController::handleSoundHeard(Sound* sound)
{
	printf("Sprite %d heard sound %d\n", sprite, sound->soundId);
}

void SpriteController::handleSpriteSeen(Sprite* sprite)
{
	//printf("Sprite %d sees sprite %d\n", this, sprite);
}

/*
// apply current action 
	if (!currAction->apply(this, ms))
	{
		printf("CivilianSprite %d starting new action\n", this);
		// current action is over: free and create new idle action TODO: MORE SOPHISTICATED DECISION PROCESS
		delete currAction;
		currAction = new IdleAction(ACTION_LOOPING);
	}
	
	
	
	printf("Civilian Attacked!!\n");
	
	// replace current action with knockback in the direction of the attack
	delete currAction;
	currAction = new KnockbackAction(attack->dir);
	
	// handle loss of hp and show healthbar
	loseHealth(attack->damage);
	healthbar->changeHealth(-attack->damage);
	showHealthbar();
	
	// add sound
	sounds.push_back(SOUND_2);
	
	// called by map when player is struck by an attack
		void handleAttacked(Attack* attack);
		// handles sprite hearing a sound
		void handleSoundHeard(Sound* sound);
		// handles sprite seeing another sprite 
		void handleSpriteSeen(Sprite* sprite);
	*/