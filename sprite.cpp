#include "sprite.h"

Sprite::Sprite(SPRITE_TYPE spriteType, AnimationEngine* animEngine)
{
	this->spriteType = spriteType;
	this->animEngine = animEngine;
	animPlayer = new AnimationPlayer(animEngine->textureAtlas);
}
	
SDL_Point Sprite::getRightHandPosition() // todo: standardize for all sprites
{
	switch (facingDir) 
	{	
		case DIRECTION_RIGHT:
			return SDL_Point { x + 16, y + 30 };

		case DIRECTION_UP:
			return SDL_Point { x + 26, y + 26 };

		case DIRECTION_DOWN:
			return SDL_Point { x + 3, y + 26 };

		case DIRECTION_LEFT:
			return SDL_Point { x + 17, y + 30 };

		default:
			printf("Weird!! Don't know which animation to show!\n");
			break;
	}
}

void Sprite::move(int ms) {
	// save current position
	lastX = x;
	lastY = y;
	
	x += ms * speedX;
	y += ms * speedY;
	
	// adjust hitbox and line of sight. 
	// they use integer coordinates so we can't simply add to them
	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
	
	lineOfSight.x = x + lineOfSightOffsetX;
	lineOfSight.y = y + lineOfSightOffsetY;	
	
}

void Sprite::startWalking()
{
	animPlayer->setAnimSequence(animEngine->get(spriteType, SPRITE_WALK, NULL));

	switch( facingDir ) 
	{ 
		case DIRECTION_RIGHT:
			speedX = walkSpeed;
			speedY = 0;
			break;					

		case DIRECTION_UP:
			speedX = 0;
			speedY = -walkSpeed;
			break;

		case DIRECTION_LEFT:
			speedX = -walkSpeed;
			speedY = 0;
			break;

		case DIRECTION_DOWN:
			speedX = 0;
			speedY = walkSpeed;
			break;
			
		default:
			printf("Sprite::startMoving received invalid facingDir! %d\n", facingDir);
	}
}

void Sprite::startRunning()
{
	animPlayer->setAnimSequence(animEngine->get(spriteType, SPRITE_RUN, NULL));
								
	switch( facingDir ) 
	{ 
		case DIRECTION_RIGHT:
			speedX = runSpeed;
			speedY = 0;
			break;					

		case DIRECTION_UP:
			speedX = 0;
			speedY = -runSpeed;
			break;

		case DIRECTION_LEFT:
			speedX = -runSpeed;
			speedY = 0;
			break;

		case DIRECTION_DOWN:
			speedX = 0;
			speedY = runSpeed;
			break;
			
		default:
			printf("Sprite::startRunning received unkown facingDir! %d\n", facingDir);
	}
}

void Sprite::stopMoving()
{
	animPlayer->setAnimSequence(animEngine->get(spriteType, SPRITE_IDLE, NULL));
								
	speedX = 0;
	speedY = 0;
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
	// change of direction: queue animPlayer TODO: MAKE SURE THE DIRECTION IS SUPPORTED
	animPlayer->setDir(dir);
	
	// set animation, direction, and lineOfSight
	switch (facingDir) 
	{	
		case DIRECTION_RIGHT:
			facingDir = DIRECTION_RIGHT;
			lineOfSightOffsetX = hitbox.w;
			lineOfSightOffsetY = 0;
			lineOfSight.w = sightDistance; // todo: center. also, hitbox is too small: want full dimensions of sprite
			lineOfSight.h = sightWidth;
			break;

		case DIRECTION_UP:
			facingDir = DIRECTION_UP;
			lineOfSightOffsetX = 0;
			lineOfSightOffsetY = -sightDistance;
			lineOfSight.w = sightWidth;
			lineOfSight.h = sightDistance;
			break;

		case DIRECTION_LEFT:
			facingDir = DIRECTION_LEFT;
			lineOfSightOffsetX = -sightDistance;
			lineOfSightOffsetY = 0;
			lineOfSight.w = sightDistance;
			lineOfSight.h = sightWidth;
			break;

		case DIRECTION_DOWN:
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
	animPlayer->update(ms);
}

void Sprite::setListener(SpriteListener* listener)
{
	this->listener = listener;
}

void Sprite::addHealth(float amount)
{
	currHp += amount;	
	// norm to fullHp
	currHp = currHp > fullHp ? fullHp : currHp;
	printf("Sprite received %f health to hit %f hp\n", amount, currHp);
	
	if (listener)
	{
		listener->onSpriteHealthChanged(amount, currHp);
	}
}

void Sprite::loseHealth(float amount)
{
	currHp -= amount;
	
	// sprite dies if hp hits zero
	if (currHp < 0)
	{
		currHp = 0;
		dead = true;	
		printf("Sprite died\n");
	}
	printf("Sprite lost %f health to hit %f hp\n", amount, currHp);
	
	if (listener)
	{
		listener->onSpriteHealthChanged(-amount, currHp);
	}
}