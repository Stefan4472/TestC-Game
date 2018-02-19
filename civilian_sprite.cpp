#include "civilian_sprite.h"

CivilianSprite::CivilianSprite(float x, float y, TextureAtlas* textureAtlas)
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
	
	idle_right_anim = new Spritesheet(textureAtlas, CIVILIAN_IDLE_RIGHT, 1, 100);
	idle_left_anim = new Spritesheet(textureAtlas, CIVILIAN_IDLE_LEFT, 1, 100);
	idle_up_anim = new Spritesheet(textureAtlas, CIVILIAN_IDLE_UP, 1, 100);
	idle_down_anim = new Spritesheet(textureAtlas, CIVILIAN_IDLE_DOWN, 1, 100);
	
	walk_right_anim = new Spritesheet(textureAtlas, CIVILIAN_WALK_RIGHT, 3, 100);
	walk_left_anim = new Spritesheet(textureAtlas, CIVILIAN_WALK_LEFT, 3, 100);
	walk_up_anim = new Spritesheet(textureAtlas, CIVILIAN_WALK_UP, 3, 100);
	walk_down_anim = new Spritesheet(textureAtlas, CIVILIAN_WALK_DOWN, 3, 100);
	
	run_right_anim = new Spritesheet(textureAtlas, CIVILIAN_RUN_RIGHT, 3, 100);
	run_left_anim = new Spritesheet(textureAtlas, CIVILIAN_RUN_LEFT, 3, 100);
	run_up_anim = new Spritesheet(textureAtlas, CIVILIAN_RUN_UP, 3, 100);
	run_down_anim = new Spritesheet(textureAtlas, CIVILIAN_RUN_DOWN, 3, 100);
	
	current_anim = idle_down_anim;
	
	fullHp = 30;
	currHp = 30;
		
	// TODO: KNOW WHICH DIRECTION SPRITE IS INITIALLY FACING. DEFAULTS TO DOWN
	setDir(DIRECTION_DOWN); // sets line of sight
	
	init();
}