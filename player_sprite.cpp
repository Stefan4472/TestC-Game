#include "player_sprite.h"

PlayerSprite::PlayerSprite(float xCoord, float yCoord, TextureAtlas* textureAtlas, SDL_Renderer* renderer) {
	printf("Creating sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;
	
	this->renderer = renderer;

	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 10;
	hitboxOffsetY = 44;
	hitbox.w = 32;
	hitbox.h = 13;
		
	idle_right_anim = new Spritesheet(textureAtlas, PLAYER_IDLE_RIGHT, 1, 100);
	idle_left_anim = new Spritesheet(textureAtlas, PLAYER_IDLE_LEFT, 1, 100);
	idle_up_anim = new Spritesheet(textureAtlas, PLAYER_IDLE_UP, 1, 100);
	idle_down_anim = new Spritesheet(textureAtlas, PLAYER_IDLE_DOWN, 1, 100);
	
	walk_right_anim = new Spritesheet(textureAtlas, PLAYER_WALK_RIGHT, 4, 100);
	walk_left_anim = new Spritesheet(textureAtlas, PLAYER_WALK_LEFT, 4, 100);
	walk_up_anim = new Spritesheet(textureAtlas, PLAYER_WALK_UP, 4, 100);
	walk_down_anim = new Spritesheet(textureAtlas, PLAYER_WALK_DOWN, 4, 100);
	
	run_right_anim = new Spritesheet(textureAtlas, PLAYER_RUN_RIGHT, 4, 100);
	run_left_anim = new Spritesheet(textureAtlas, PLAYER_RUN_LEFT, 4, 100);
	run_up_anim = new Spritesheet(textureAtlas, PLAYER_RUN_UP, 4, 100);
	run_down_anim = new Spritesheet(textureAtlas, PLAYER_RUN_DOWN, 4, 100);
	
	current_anim = idle_down_anim;
	
	fullHp = 100;
	currHp = 100;
	
	init();
}

SDL_Point PlayerSprite::getRightHandPosition()
{
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

void PlayerSprite::drawTo(SDL_Renderer* renderer, int offsetX, int offsetY) {
	// draw current animation frame to screen
	/*(*current_anim).drawTo(renderer, x - offsetX, y - offsetY);
	
	// draw in-hand item (if any)
	if (inHand)
	{
		SDL_Point hand_location = getRightHandPosition();
		inHand->drawTo(renderer, (int) (hand_location.x - offsetX), (int) (hand_location.y - offsetY));
	}*/
	Sprite::drawTo(renderer, offsetX, offsetY);
}