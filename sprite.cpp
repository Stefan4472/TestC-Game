#include "sprite.h"

void Sprite::init()
{
	idle_anims[1] = idle_up_anim;
	idle_anims[2] = idle_down_anim;
	idle_anims[3] = idle_right_anim;
	idle_anims[4] = idle_left_anim;
	
	walk_anims[1] = walk_up_anim; // TODO: MORE ELEGANT WAY?
	walk_anims[2] = walk_down_anim;
	walk_anims[3] = walk_right_anim;
	walk_anims[4] = walk_left_anim;
	
	run_anims[1] = run_up_anim;
	run_anims[2] = run_down_anim;
	run_anims[3] = run_right_anim;
	run_anims[4] = run_left_anim;
}

void Sprite::onInHandItemChanged(Item* item)
{
	printf("Sprite: on hand changed to %s\n", item->name);
	inHand = item;
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
	current_anim_array = walk_anims;
	current_anim = current_anim_array[facingDir];

	switch( facingDir ) 
	{ 
		case DIRECTION_RIGHT:
			speedX = walkSpeed;
			speedY = 0;
			//current_anim = walk_right_anim;
			break;					

		case DIRECTION_UP:
			speedX = 0;
			speedY = -walkSpeed;
			//current_anim = walk_up_anim;
			break;

		case DIRECTION_LEFT:
			speedX = -walkSpeed;
			speedY = 0;
			//current_anim = walk_left_anim;
			break;

		case DIRECTION_DOWN:
			speedX = 0;
			speedY = walkSpeed;
			//current_anim = walk_down_anim;
			break;
			
		default:
			printf("Sprite::startMoving received unkown facingDir! %d\n", facingDir);
	}
}

void Sprite::startRunning()
{
	current_anim_array = run_anims;
	current_anim = current_anim_array[facingDir];
	switch( facingDir ) 
	{ 
		case DIRECTION_RIGHT:
			speedX = runSpeed;
			speedY = 0;
			//current_anim = run_right_anim;
			break;					

		case DIRECTION_UP:
			speedX = 0;
			speedY = -runSpeed;
			//current_anim = run_up_anim;
			break;

		case DIRECTION_LEFT:
			speedX = -runSpeed;
			speedY = 0;
			//current_anim = run_left_anim;
			break;

		case DIRECTION_DOWN:
			speedX = 0;
			speedY = runSpeed;
			//current_anim = run_down_anim;
			break;
			
		default:
			printf("Sprite::startRunning received unkown facingDir! %d\n", facingDir);
	}
}

void Sprite::stopMoving()
{
	speedX = 0;
	speedY = 0;
	
	current_anim_array = idle_anims;
	current_anim = current_anim_array[facingDir];
	
	/*switch( facingDir ) 
	{ 
		case DIRECTION_RIGHT:
			current_anim = idle_right_anim;
			break;					

		case DIRECTION_UP:
			current_anim = idle_up_anim;
			break;

		case DIRECTION_LEFT:
			current_anim = idle_left_anim;
			break;

		case DIRECTION_DOWN:
			current_anim = idle_down_anim;
			break;
			
		default:
			printf("Sprite::stopMoving received unkown facingDir! %d\n", facingDir);
	}*/
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
		current_anim->reset(); 
		facingDir = dir;
	
		current_anim = current_anim_array[facingDir];
	}
	
	// set animation, direction, and lineOfSight
	switch (facingDir) 
	{	
		case DIRECTION_RIGHT:
			//current_anim = walk_right_anim; // TODO: NEED TO SET TO SAME ACTION AS CURRENTLY DOING (WALK, IDLE, RUN)
			facingDir = DIRECTION_RIGHT;
			lineOfSightOffsetX = hitbox.w;
			lineOfSightOffsetY = 0;
			lineOfSight.w = sightDistance; // todo: center. also, hitbox is too small: want full dimensions of sprite
			lineOfSight.h = sightWidth;
			break;

		case DIRECTION_UP:
			//current_anim = walk_up_anim;
			facingDir = DIRECTION_UP;
			lineOfSightOffsetX = 0;
			lineOfSightOffsetY = -sightDistance;
			lineOfSight.w = sightWidth;
			lineOfSight.h = sightDistance;
			break;

		case DIRECTION_LEFT:
			//current_anim = walk_left_anim;
			facingDir = DIRECTION_LEFT;
			lineOfSightOffsetX = -sightDistance;
			lineOfSightOffsetY = 0;
			lineOfSight.w = sightDistance;
			lineOfSight.h = sightWidth;
			break;

		case DIRECTION_DOWN:
			//current_anim = walk_down_anim;
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
	current_anim->passTime(ms);
	if (current_anim->paused)
	{
		printf("An animation is paused\n");	
	}
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

void Sprite::drawTo(SDL_Renderer* renderer, int offsetX, int offsetY)
{
	// draw current animation frame to screen
	current_anim->drawTo(renderer, x - offsetX, y - offsetY);
	
	// draw in-hand item (if any)
	if (inHand)
	{
		SDL_Point hand_location = getRightHandPosition();
		inHand->drawTo(renderer, (int) (hand_location.x - offsetX), (int) (hand_location.y - offsetY));
	}
}