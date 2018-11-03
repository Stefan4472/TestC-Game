#include "sprite_controller.h"

SpriteController::SpriteController(Sprite* sprite, Inventory* inventory,
	TextureAtlas* textureAtlas, AnimationEngine* animEngine)
{
	this->sprite = sprite;
	sprite->setListener(this);

	this->inventory = inventory;
	inventory->setListener(this);

	this->animEngine = animEngine;
	animPlayer = new AnimationPlayer(textureAtlas);
}

void SpriteController::onInHandItemChanged(Item* newItem)
{
	inHand = newItem;

}

void SpriteController::onSpriteHealthChanged(int amount, int newHp)
{
	printf("SpriteController received onSpriteHealthChanged callback for %d and %d. Showing Healthbar\n", amount, currHp);
	// set healthbar to show for 200 ms
	showHealthbarMs += 200;

	if (newHp <= 0)
	{
		handleSpriteDead();
	}
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
	// update animation
	animPlayer->update(ms);

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
	if (inHand && inHand->destroy)
	{
		delete inHand;
		inHand = NULL;
	}
	else if (inHand)
	{
		inHand->update(ms);
	}

	// decrement remaining time to show health bar (if any)
	showHealthbarMs = (showHealthbarMs > ms ? showHealthbarMs - ms : 0);
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

void Sprite::handleSpriteDead()
{
	sprite->dead = true;
	sprite->destroy = true;
}

void SpriteController::drawTo(SDL_Renderer* renderer, TextureAtlas* textureAtlas)
{
	// draw sprite's current animation
	animPlayer->drawTo(renderer, sprite->x, sprite->y);

	// draw in-hand
	if (inHand) // TODO: THIS SHOULD BE TAKEN CARE OF BY THE ANIMATION ENGINE
	{
		SDL_Point hand_location = sprite->getRightHandPosition();
		textureAtlas->draw(renderer, inHand->textureId, (int) (hand_location.x), (int) (hand_location.y));
		//inHand->drawTo(renderer, (int) (hand_location.x - offsetX), (int) (hand_location.y - offsetY));
	}

	// draw health bar
	if (showHealthbarMs)
	{
		healthbar->drawTo(renderer, sprite->x - offsetX, sprite->y - offsetY);
	}
}
