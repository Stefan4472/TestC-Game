#include "sprite.h"

void Sprite::onInHandChanged(int id)
{
	printf("Sprite: on hand changed to %d\n", id);
}

void Sprite::onHealthChanged()
{
	printf("Sprite received onHealthChanged");
}
			
void Sprite::move(int ms) {
	// save current position
	lastX = x;
	lastY = y;
	
	if (movementDir == DIRECTION_RIGHT) {
		x += ms * PX_PER_MS;
	} else if (movementDir == DIRECTION_LEFT) {
		x -= ms * PX_PER_MS;
	}

	if (movementDir == DIRECTION_UP) {
		y -= ms * PX_PER_MS;
	} else if (movementDir == DIRECTION_DOWN) {
		y += ms * PX_PER_MS;
	}	
	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
}

void Sprite::moveBack() 
{
	x = lastX;
	y = lastY;

	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
}

void Sprite::changeDir(int newDir)
{
	// only change if direction has been changed
	if (newDir != movementDir) {
		
		// reset currently-playing animation
		(*current_anim).reset();
		
		movementDir = newDir;
		
		switch (movementDir) 
		{	
			// no movement: simply pause animation that was playing. This way, the sprite remains
			// facing the same direction
			case DIRECTION_NONE:
				//current_anim = &idle_anim;
				current_anim->pause();
				break;

			case DIRECTION_RIGHT:
				current_anim = &mv_right_anim;
				current_anim->play();
				facingDir = DIRECTION_RIGHT;
				break;

			case DIRECTION_UP:
				current_anim = &mv_up_anim;
				current_anim->play();
				facingDir = DIRECTION_UP;
				break;

			case DIRECTION_DOWN:
				current_anim = &mv_down_anim;
				current_anim->play();
				facingDir = DIRECTION_DOWN;
				break;

			case DIRECTION_LEFT:
				current_anim = &mv_left_anim;
				current_anim->play();
				facingDir = DIRECTION_LEFT;
				break;

			default:
				printf("Weird!! Don't know which animation to show!\n");
				break;
		}
	}
}

void Sprite::handleTrigger(Trigger* trigger)
{
	printf("Sprite baseclass received trigger %d\n", trigger->triggerType);	
}

void Sprite::update(int ms) {
	(*current_anim).passTime(ms);
}

void Sprite::addHealth(float amount)
{
	currHp += amount;	
	// norm to fullHp
	currHp = currHp > fullHp ? fullHp : currHp;
	printf("Sprite received %f health to hit %f hp\n", amount, currHp);
}

void Sprite::loseHealth(float amount)
{
	currHp -= amount;
	// norm to zero
	currHp = currHp < 0 ? 0 : currHp;
	printf("Sprite lost %d health to hit %d hp\n", amount, currHp);
}