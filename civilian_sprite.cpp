#include "civilian_sprite.h"

void CivilianSprite::init(float xCoord, float yCoord, 
					 SDL_Surface* idle_anim_sheet, 
					 SDL_Surface* mv_up_anim_sheet, 
					 SDL_Surface* mv_down_anim_sheet, 
				 	 SDL_Surface* mv_left_anim_sheet, 
				 	 SDL_Surface* mv_right_anim_sheet) {
	printf("Creating civilian sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;

	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 8;
	hitboxOffsetY = 4;
	hitbox.w = 30;
	hitbox.h = 44;
	
	idle_anim.init(idle_anim_sheet, 1, 100);
	mv_up_anim.init(mv_up_anim_sheet, 3, 100);
	mv_down_anim.init(mv_down_anim_sheet, 3, 100);
	mv_left_anim.init(mv_left_anim_sheet, 3, 100);
	mv_right_anim.init(mv_right_anim_sheet, 3, 100);
	
	current_anim = &idle_anim;
}

void CivilianSprite::move(int ms) {
	if (movementDir == MOVEMENT_RIGHT) {
		x += ms * PX_PER_MS;
	} else if (movementDir == MOVEMENT_LEFT) {
		x -= ms * PX_PER_MS;
	}

	if (movementDir == MOVEMENT_UP) {
		y -= ms * PX_PER_MS;
	} else if (movementDir == MOVEMENT_DOWN) {
		y += ms * PX_PER_MS;
	}	
	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
}

void CivilianSprite::changeDir(int newDir)
{
	// only change if direction has been changed
	if (newDir != movementDir) {
		
		// reset currently-playing animation
		(*current_anim).reset();
		
		movementDir = newDir;
		
		switch (movementDir) 
		{	
			case MOVEMENT_NONE:
				current_anim = &idle_anim;
				break;

			case MOVEMENT_RIGHT:
				printf("Changing to right\n");
				current_anim = &mv_right_anim;
				break;

			case MOVEMENT_UP:
				current_anim = &mv_up_anim;
				break;

			case MOVEMENT_DOWN:
				current_anim = &mv_down_anim;
				break;

			case MOVEMENT_LEFT:
				current_anim = &mv_left_anim;
				break;

			default:
				printf("Weird!! Don't know which animation to show!\n");
				break;
		}
	}
}

/*void PlayerSprite::moveBack() 
{
	printf("Moving back to %f, %f from %f, %f\n", lastX, lastY, x, y);
	x = lastX;
	y = lastY;

	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
	
}*/

void CivilianSprite::update(int ms) {
	(*current_anim).passTime(ms);
	if (x < 100) 
	{
		changeDir(MOVEMENT_RIGHT);
	}
	else if (x > 250) 
	{
		changeDir(MOVEMENT_LEFT);
	}
}

void CivilianSprite::drawTo(SDL_Surface* screenSurface, int offsetX, int offsetY) {
	// draw current animatino frame to screen
	(*current_anim).drawTo(screenSurface, x - offsetX, y - offsetY);
}