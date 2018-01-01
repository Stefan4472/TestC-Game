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

	speedPerMs = 0.1f;
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

void CivilianSprite::update(int ms) {
	// apply current action 
	defaultAction->apply(this, ms);
	(*current_anim).passTime(ms);
	
	/*if (x < 100) 
	{
		changeDir(MOVEMENT_RIGHT);
	}
	else if (x > 250) 
	{
		changeDir(MOVEMENT_LEFT);
	}*/
}

void CivilianSprite::drawTo(SDL_Surface* screenSurface, int offsetX, int offsetY) {
	// draw current animatino frame to screen
	(*current_anim).drawTo(screenSurface, x - offsetX, y - offsetY);
}