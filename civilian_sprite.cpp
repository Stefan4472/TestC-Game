#include "civilian_sprite.h"

CivilianSprite::CivilianSprite(float xCoord, float yCoord, Sprite* playerSprite, TextureAtlas* textureAtlas)
{
	printf("Creating civilian sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;
	this->playerSprite = playerSprite;
	speedPerMs = 0.1f;
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
	
	inventory = new Inventory(5);	
	
	fullHp = 30;
	currHp = 30;

	currAction = getInitialAction();
	
	// TODO: KNOW WHICH DIRECTION SPRITE IS INITIALLY FACING. DEFAULTS TO DOWN
}

void CivilianSprite::update(int ms) {
	// apply current action 
	currAction->apply(this, ms);
	(*current_anim).passTime(ms);
}

SDL_Point CivilianSprite::getRightHandPosition()
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
void CivilianSprite::drawTo(SDL_Renderer* renderer, int offsetX, int offsetY) {
	// draw current animatino frame to screen
	(*current_anim).drawTo(renderer, x - offsetX, y - offsetY);
}