#include "civilian_sprite.h"

CivilianSprite::CivilianSprite()
{
	inventory = new Inventory(5);	
}

CivilianSprite::CivilianSprite(float xCoord, float yCoord, Sprite* playerSprite, TextureAtlas* textureAtlas)
{
	init(xCoord, yCoord, playerSprite, textureAtlas);
}

void CivilianSprite::init(float xCoord, float yCoord, Sprite* playerSprite, TextureAtlas* textureAtlas) {
	printf("Creating civilian sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;
	this->playerSprite = playerSprite;
	//defaultAction = new FollowAction(10, playerSprite, 10);
	defaultAction = new IdleAction(ACTION_LOOPING);
	speedPerMs = 0.1f;
	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 8;
	hitboxOffsetY = 4;
	hitbox.w = 30;
	hitbox.h = 44;
	
	idle_anim.init(textureAtlas, CIVILIAN_IDLE, 1, 100);
	mv_up_anim.init(textureAtlas, CIVILIAN_MVUP, 3, 100);
	mv_down_anim.init(textureAtlas, CIVILIAN_MVDOWN, 3, 100);
	mv_left_anim.init(textureAtlas, CIVILIAN_MVLEFT, 3, 100);
	mv_right_anim.init(textureAtlas, CIVILIAN_MVRIGHT, 3, 100);
	
	current_anim = &idle_anim;
	
	inventory = new Inventory(5);	
	
	fullHp = 30;
	currHp = 30;
}

void CivilianSprite::update(int ms) {
	// apply current action 
	defaultAction->apply(this, ms);
	(*current_anim).passTime(ms);
}

void CivilianSprite::drawTo(SDL_Surface* screenSurface, int offsetX, int offsetY) {
	// draw current animatino frame to screen
	(*current_anim).drawTo(screenSurface, x - offsetX, y - offsetY);
}