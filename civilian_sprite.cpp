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