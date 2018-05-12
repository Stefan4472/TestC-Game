#include "sprite.h"

Sprite::Sprite(int spriteType, float x, float y, AnimationEngine* animEngine)
{
	printf("Sprite received animEngine %d\n", animEngine);
	printf("Creating Sprite of type %d at %f, %f...\n", spriteType, x, y);
	this->spriteType = spriteType;
	this->x = x;
	this->y = y;
	this->animEngine = animEngine;
	animPlayer = new AnimationPlayer(animEngine->textureAtlas);

	if (spriteType == SPRITE_TYPE_CIVILIAN)
	{
		walkSpeed = 0.1f;
		runSpeed = 0.2f;
		// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
		hitboxOffsetX = 7;
		hitboxOffsetY = 25;
		hitbox.w = 20;
		hitbox.h = 6;

		fullHp = 30;
		currHp = 30;
	}
	else if (spriteType == SPRITE_TYPE_PLAYER)
	{
		hitboxOffsetX = 10;
		hitboxOffsetY = 44;
		hitbox.w = 32;
		hitbox.h = 13;

		fullHp = 100;
		currHp = 100;
	}
	else
	{
		printf("EXCEPTION: Invalid Sprite Type %d\n", spriteType);
	}

	//printf(animEngine->get(spriteType, SPRITE_IDLE, NULL)->toString());
	animPlayer->setAnimSequence(animEngine->get(spriteType, SPRITE_IDLE, NULL));
	setDir(DIRECTION_DOWN);
	printf("Done\n");
}

SDL_Point Sprite::getRightHandPosition() // todo: standardize for all sprites
{
	// TODO: JUST USE ON SPRITE MODEL SO THIS WORKS FOR ALL (CURRENTLY WILL BE OFF FOR CIVILIAN)
	switch (facingDir)
	{
		case DIRECTION_RIGHT:
			return SDL_Point { x + 24, y + 44 };

		case DIRECTION_UP:
			return SDL_Point { x + 42, y + 41 };

		case DIRECTION_DOWN:
			return SDL_Point { x + 13, y + 40 };

		case DIRECTION_LEFT:
			return SDL_Point { x + 19, y + 41 };

		default:
			printf("Weird!! PlayerSprite, don't know which animation to show!\n");
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
	switch (dir)
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
