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
	
	x += ms * speedX;
	y += ms * speedY;
	
	/*hitbox.x += ms * speedX; // TODO: CLEANUP
	hitbox.y += ms * speedY;
	
	lineOfSight.x += ms * speedX;
	lineOfSight.y += ms * speedY;	
	*/
	/*
	if (movementDir == DIRECTION_RIGHT) {
		x += ms * moveSpeed;
	} else if (movementDir == DIRECTION_LEFT) {
		x -= ms * moveSpeed;
	}

	if (movementDir == DIRECTION_UP) {
		y -= ms * moveSpeed;
	} else if (movementDir == DIRECTION_DOWN) {
		y += ms * moveSpeed;
	}*/	
	
	
	// adjust hitbox and line of sight
	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
	
	lineOfSight.x = x + lineOfSightOffsetX;
	lineOfSight.y = y + lineOfSightOffsetY;	
	
}

void Sprite::startWalking()
{
	switch( facingDir ) 
	{ 
		case DIRECTION_RIGHT:
			speedX = moveSpeed;
			speedY = 0;
			break;					

		case DIRECTION_UP:
			speedX = 0;
			speedY = -moveSpeed;
			break;

		case DIRECTION_LEFT:
			speedX = -moveSpeed;
			speedY = 0;
			break;

		case DIRECTION_DOWN:
			speedX = 0;
			speedY = moveSpeed;
			break;
			
		default:
			printf("Sprite::startMoving received unkown facingDir! %d\n", facingDir);
	}
	current_anim->play();
}

void Sprite::stopMoving()
{
	speedX = 0;
	speedY = 0;
	current_anim->pause();
	current_anim->reset();
}

void Sprite::moveBack() 
{
	x = lastX;
	y = lastY;

	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
}

void Sprite::setDir(int dir)
{
	// change of direction: reset current animation
	if (dir != facingDir) 
	{
		(*current_anim).reset(); 
		facingDir = dir;
	}
	// set animation, direction, and lineOfSight
	switch (facingDir) 
	{	
		case DIRECTION_RIGHT:
			current_anim = &mv_right_anim;
			facingDir = DIRECTION_RIGHT;
			lineOfSightOffsetX = hitbox.w;
			lineOfSightOffsetY = 0;
			lineOfSight.w = sightDistance; // todo: center. also, hitbox is too small: want full dimensions of sprite
			lineOfSight.h = sightWidth;
			break;

		case DIRECTION_UP:
			current_anim = &mv_up_anim;
			facingDir = DIRECTION_UP;
			lineOfSightOffsetX = 0;
			lineOfSightOffsetY = -sightDistance;
			lineOfSight.w = sightWidth;
			lineOfSight.h = sightDistance;
			break;

		case DIRECTION_LEFT:
			current_anim = &mv_left_anim;
			facingDir = DIRECTION_LEFT;
			lineOfSightOffsetX = -sightDistance;
			lineOfSightOffsetY = 0;
			lineOfSight.w = sightDistance;
			lineOfSight.h = sightWidth;
			break;
			
		case DIRECTION_DOWN:
			current_anim = &mv_down_anim;
			facingDir = DIRECTION_DOWN;
			lineOfSightOffsetX = 0;
			lineOfSightOffsetY = hitbox.h;
			lineOfSight.w = sightWidth;
			lineOfSight.h = sightDistance;
			break;

		default:
			printf("Weird!! Don't know which animation to show! Facing dir = %d\n", facingDir);
			break;
	}
}

void Sprite::update(int ms) {
	// only animate if moving
	if (speedX || speedY)
	{
		(*current_anim).passTime(ms);
	}
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

void Sprite::drawTo(SDL_Renderer* renderer, int offsetX, int offsetY)
{
	// draw current animation frame to screen
	(*current_anim).drawTo(renderer, x - offsetX, y - offsetY);
	
	// draw in-hand item (if any)
	if (inHand)
	{
		SDL_Point hand_location = getRightHandPosition();
		inHand->drawTo(renderer, (int) (hand_location.x - offsetX), (int) (hand_location.y - offsetY));
	}
}