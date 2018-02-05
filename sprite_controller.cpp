#include "sprite_controller.h"

SpriteController::SpriteController(Sprite* sprite)
{
	this->sprite = sprite;
}

void SpriteController::handleMapCollision()
{
	sprite->moveBack();	// TODO: SEND TO TOP ACTION ON ACTIONSTACK?
}

void SpriteController::handleSpriteCollision(Sprite* other)
{
	sprite->moveBack(); // TODO: SEND TO CURRENT ACTION, IF ANY
}
			
void SpriteController::update(int ms)
{
	// update attacks, removing those that are finished
	for (int i = 0; i < attacks.size(); )
	{
		attacks[i]->update(ms);
		if (attacks[i]->finished)
		{
			delete attacks[i];
			attacks.erase(attacks.begin() + i);
		}
		else
		{
			i++;	
		}
	}
	// TODO: UPDATE IN-HAND ITEM, IF ANY
	if (sprite->inHand)
	{
		
	}
}

/*
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
}*/