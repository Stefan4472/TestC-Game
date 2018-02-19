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
	
	// apply buffs, if any, and removes those that are finished
	for (int i = 0; i < buffs.size();)
	{
		if (buffs[i]->apply(sprite, ms))
		{
			printf("Applying buff to %d\n", sprite);
			i++;	
		}
		else
		{
			printf("Deleting buff\n");
			delete buffs[i];
			buffs.erase(buffs.begin() + i);
		}
	}
	
	// update in-hand item, if any, and delete if requested
	if (sprite->inHand)
	{
		if (sprite->inHand->destroy)
		{
			delete sprite->inHand;
		}
		sprite->inHand->update(ms);
	}
}

void SpriteController::handleAttacked(Attack* attack)
{
	return;
}

void SpriteController::handleSoundHeard(Sound* sound)
{
	return;
}

void SpriteController::handleSpriteSeen(Sprite* sprite)
{
	return;
}