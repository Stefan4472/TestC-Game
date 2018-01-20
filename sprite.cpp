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
		x += ms * moveSpeed;
	} else if (movementDir == DIRECTION_LEFT) {
		x -= ms * moveSpeed;
	}

	if (movementDir == DIRECTION_UP) {
		y -= ms * moveSpeed;
	} else if (movementDir == DIRECTION_DOWN) {
		y += ms * moveSpeed;
	}	
	
	// adjust hitbox and line of sight
	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
	
	lineOfSight.x = x + lineOfSightOffsetX;
	lineOfSight.y = y + lineOfSightOffsetY;	
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
				printf("R\n");
				current_anim = &mv_right_anim;
				current_anim->play();
				facingDir = DIRECTION_RIGHT;
				lineOfSightOffsetX = hitbox.w;
				lineOfSightOffsetY = 0;
				lineOfSight.w = sightDistance; // todo: center. also, hitbox is too small: want full dimensions of sprite
				lineOfSight.h = sightWidth;
				printf("%d, %d w/h %d, %d\n", lineOfSight.x, lineOfSight.y, lineOfSight.w, lineOfSight.h);
				break;

			case DIRECTION_UP:
				printf("U\n");
				current_anim = &mv_up_anim;
				current_anim->play();
				facingDir = DIRECTION_UP;
				lineOfSightOffsetX = 0;
				lineOfSightOffsetY = -sightDistance;
				lineOfSight.w = sightWidth;
				lineOfSight.h = sightDistance;
				printf("%d, %d w/h %d, %d\n", lineOfSight.x, lineOfSight.y, lineOfSight.w, lineOfSight.h);
				break;

			case DIRECTION_DOWN:
				printf("D\n");
				current_anim = &mv_down_anim;
				current_anim->play();
				facingDir = DIRECTION_DOWN;
				lineOfSightOffsetX = 0;
				lineOfSightOffsetY = hitbox.h;
				lineOfSight.w = sightWidth;
				lineOfSight.h = sightDistance;
				printf("%d, %d w/h %d, %d\n", lineOfSight.x, lineOfSight.y, lineOfSight.w, lineOfSight.h);
				break;

			case DIRECTION_LEFT:
				printf("L\n");
				current_anim = &mv_left_anim;
				current_anim->play();
				facingDir = DIRECTION_LEFT;
				lineOfSightOffsetX = -sightDistance;
				lineOfSightOffsetY = 0;
				lineOfSight.w = sightDistance;
				lineOfSight.h = sightWidth;
				printf("%d, %d w/h %d, %d\n", lineOfSight.x, lineOfSight.y, lineOfSight.w, lineOfSight.h);
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