#include "civilian_sprite.h"

CivilianSprite::CivilianSprite(float x, float y, TextureAtlas* textureAtlas) : Sprite(SPRITE_TYPE_CIVILIAN)
{
	printf("Creating civilian sprite at %f, %f\n", x, y);
	
	this->x = x;
	this->y = y;
	walkSpeed = 0.1f;
	runSpeed = 0.2f;
	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 7;
	hitboxOffsetY = 25;
	hitbox.w = 20;
	hitbox.h = 6;
	
	fullHp = 30;
	currHp = 30;
		
	// TODO: KNOW WHICH DIRECTION SPRITE IS INITIALLY FACING. DEFAULTS TO DOWN
	setDir(DIRECTION_DOWN); // sets line of sight
}