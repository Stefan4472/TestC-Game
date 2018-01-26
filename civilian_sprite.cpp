#include "civilian_sprite.h"

CivilianSprite::CivilianSprite(float xCoord, float yCoord, Sprite* playerSprite, TextureAtlas* textureAtlas)
{
	printf("Creating civilian sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;
	this->playerSprite = playerSprite;
	moveSpeed = 0.1f;
	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 7;
	hitboxOffsetY = 25;
	hitbox.w = 20;
	hitbox.h = 6;
	
	idle_anim.init(textureAtlas, CIVILIAN_IDLE, 1, 100);
	mv_up_anim.init(textureAtlas, CIVILIAN_MVUP, 3, 100);
	mv_down_anim.init(textureAtlas, CIVILIAN_MVDOWN, 3, 100);
	mv_left_anim.init(textureAtlas, CIVILIAN_MVLEFT, 3, 100);
	mv_right_anim.init(textureAtlas, CIVILIAN_MVRIGHT, 3, 100);
	
	current_anim = &idle_anim;
	
	inventory = new Inventory(this, 5);	
	
	fullHp = 30;
	currHp = 30;
	healthbar = new SpriteHealthBar(32, currHp,fullHp);

	currAction = getInitialAction();
		
	// TODO: KNOW WHICH DIRECTION SPRITE IS INITIALLY FACING. DEFAULTS TO DOWN
	setDir(DIRECTION_DOWN); // sets line of sight
}

void CivilianSprite::update(int ms) {
	// apply current action 
	if (!currAction->apply(this, ms))
	{
		printf("CivilianSprite %d starting new action\n", this);
		// current action is over: free and create new idle action TODO: MORE SOPHISTICATED DECISION PROCESS
		delete currAction;
		currAction = new IdleAction(ACTION_LOOPING);
	}
	
	// only animate if moving
	if (speedX || speedY)
	{
		(*current_anim).passTime(ms);
	}
}

SDL_Point CivilianSprite::getRightHandPosition() // todo: standardize for all sprites
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

void CivilianSprite::handleAttacked(Attack* attack)
{
	printf("Civilian Attacked!!\n");
	
	// replace current action with knockback in the direction of the attack
	delete currAction;
	currAction = new KnockbackAction(attack->dir);
	
	// handle loss of hp and show healthbar
	loseHealth(attack->damage);
	healthbar->changeHealth(-attack->damage);
	showHealthbar();
	
	// add sound
	sounds.push_back(SOUND_2);
}

void CivilianSprite::handleSoundHeard(Sound* sound)
{
	printf("Sprite %d heard sound %d\n", this, sound->soundId);
}

void CivilianSprite::handleSpriteSeen(Sprite* sprite)
{
	//printf("Sprite %d sees sprite %d\n", this, sprite);
}

void CivilianSprite::showHealthbar() 
{
	numHealthbarFrames += 200;	
}

void CivilianSprite::drawTo(SDL_Renderer* renderer, int offsetX, int offsetY) {
	// draw current animatino frame to screen
	current_anim->drawTo(renderer, x - offsetX, y - offsetY);
	// draw healthbar, if visible
	if (numHealthbarFrames)
	{
		healthbar->drawTo(renderer, x - offsetX, y - offsetY);
		numHealthbarFrames--;
	}
}