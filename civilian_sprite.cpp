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
	
	fullHp = 30;
	currHp = 30;
	healthbar = new SpriteHealthBar(32, currHp,fullHp);
		
	// TODO: KNOW WHICH DIRECTION SPRITE IS INITIALLY FACING. DEFAULTS TO DOWN
	setDir(DIRECTION_DOWN); // sets line of sight
}

void CivilianSprite::update(int ms) {
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

void CivilianSprite::showHealthbar() 
{
	numHealthbarFrames += 200;	
}

void CivilianSprite::drawTo(SDL_Renderer* renderer, int offsetX, int offsetY) {
	// draw current animation frame to screen
	(*current_anim).drawTo(renderer, x - offsetX, y - offsetY);
	
	// draw in-hand item (if any)
	if (inHand)
	{
		SDL_Point hand_location = getRightHandPosition();
		inHand->drawTo(renderer, (int) (hand_location.x - offsetX), (int) (hand_location.y - offsetY));
	}
	
	// draw healthbar, if visible
	if (numHealthbarFrames)
	{
		healthbar->drawTo(renderer, x - offsetX, y - offsetY);
		numHealthbarFrames--; // TODO: USE MILLISECONDS, NOT FRAME COUNT (?)
	}
}