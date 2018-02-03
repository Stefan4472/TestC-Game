#include "civilian_sprite.h"

CivilianSprite::CivilianSprite(float xCoord, float yCoord, Sprite* CIVILIANSprite, TextureAtlas* textureAtlas)
{
	printf("Creating civilian sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;
	this->playerSprite = playerSprite;
	walkSpeed = 0.1f;
	runSpeed = 0.2f;
	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 7;
	hitboxOffsetY = 25;
	hitbox.w = 20;
	hitbox.h = 6;
	
	idle_right_anim = new Spritesheet(textureAtlas, CIVILIAN_IDLE_RIGHT, 1, 100);
	idle_left_anim = new Spritesheet(textureAtlas, CIVILIAN_IDLE_LEFT, 1, 100);
	idle_up_anim = new Spritesheet(textureAtlas, CIVILIAN_IDLE_UP, 1, 100);
	idle_down_anim = new Spritesheet(textureAtlas, CIVILIAN_IDLE_DOWN, 1, 100);
	
	walk_right_anim = new Spritesheet(textureAtlas, CIVILIAN_WALK_RIGHT, 4, 100);
	walk_left_anim = new Spritesheet(textureAtlas, CIVILIAN_WALK_LEFT, 4, 100);
	walk_up_anim = new Spritesheet(textureAtlas, CIVILIAN_WALK_UP, 4, 100);
	walk_down_anim = new Spritesheet(textureAtlas, CIVILIAN_WALK_DOWN, 4, 100);
	
	run_right_anim = new Spritesheet(textureAtlas, CIVILIAN_RUN_RIGHT, 4, 100);
	run_left_anim = new Spritesheet(textureAtlas, CIVILIAN_RUN_LEFT, 4, 100);
	run_up_anim = new Spritesheet(textureAtlas, CIVILIAN_RUN_UP, 4, 100);
	run_down_anim = new Spritesheet(textureAtlas, CIVILIAN_RUN_DOWN, 4, 100);
	
	current_anim = idle_down_anim;
	
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
		current_anim->passTime(ms);
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
	current_anim->drawTo(renderer, x - offsetX, y - offsetY);
	
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