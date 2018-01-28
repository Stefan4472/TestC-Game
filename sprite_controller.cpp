#include "sprite_controller.h"

SpriteController::SpriteController(Sprite* sprite)
{
	this->sprite = sprite;
	currAction = new WanderAction(ACTION_LOOPING, 10, 400, 100);
}

void SpriteController::update(int ms)
{
	currAction->apply(sprite, ms);
}