#include "player_sprite_controller.h"

PlayerSpriteController::PlayerSpriteController(PlayerSprite* playerSprite) : SpriteController(playerSprite)
{
	player = playerSprite;
}

void PlayerSpriteController::update(int ms)
{
	player->update(ms);
}

void PlayerSpriteController::handleAttacked(Attack* attack)
{
	return;
/*	printf("Civilian Attacked!!\n");
	
	// replace current action with knockback in the direction of the attack
	//delete currAction;
	//currAction = new KnockbackAction(attack->dir);
	
	// handle loss of hp and show healthbar
	sprite->loseHealth(attack->damage);
	sprite->healthbar->changeHealth(-attack->damage);
	//sprite->showHealthbar();
	
	// add sound
	sprite->sounds.push_back(SOUND_2);*/
}

void PlayerSpriteController::handleSoundHeard(Sound* sound)
{
	return;
}

void PlayerSpriteController::handleSpriteSeen(Sprite* sprite)
{
	return;
}
