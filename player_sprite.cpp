#include "player_sprite.h"

PlayerSprite::PlayerSprite(float xCoord, float yCoord, 
					 SDL_Surface* idle_anim_sheet, 
					 SDL_Surface* mv_up_anim_sheet, 
					 SDL_Surface* mv_down_anim_sheet, 
				 	 SDL_Surface* mv_left_anim_sheet, 
				 	 SDL_Surface* mv_right_anim_sheet) {
	printf("Creating sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;

	idle_anim.init(idle_anim_sheet, 1);
	mv_up_anim.init(mv_up_anim_sheet, 4);
	mv_down_anim.init(mv_down_anim_sheet, 4);
	mv_left_anim.init(mv_left_anim_sheet, 4);
	mv_right_anim.init(mv_right_anim_sheet, 4);
}

bool PlayerSprite::handleKeyEvent(SDL_Event e) 
{
	printf("PlayerSprite attempting to handle KeyEvent\n");
	
	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) 
		{
			case SDLK_RIGHT:
			case SDLK_UP:
			case SDLK_LEFT:
			case SDLK_DOWN:
				movementDir = MOVEMENT_NONE;
				return true;

			default:
				return false;
		}
	} 
	else {
		switch( e.key.keysym.sym )
		{ 
			case SDLK_RIGHT:
				movementDir = MOVEMENT_RIGHT;
				return true;					

			case SDLK_UP:
				movementDir = MOVEMENT_UP;
				return true;

			case SDLK_LEFT:
				movementDir = MOVEMENT_LEFT;
				return true;

			case SDLK_DOWN:
				movementDir = MOVEMENT_DOWN;
				return true;

			default:
				return false;
		}
	}
}

void PlayerSprite::move(int ms) {
	if (movementDir == MOVEMENT_RIGHT) {
		//x += 2;
	} else if (movementDir == MOVEMENT_LEFT) {
		//x -= 2;
	}

	if (movementDir == MOVEMENT_UP) {
		//y -= 2;
	} else if (movementDir == MOVEMENT_DOWN) {
		//y += 2;
	}	
}

void PlayerSprite::changeDir(int newDir) {
	
}

void PlayerSprite::update(int ms) {
	
}

void PlayerSprite::drawTo(SDL_Surface* screenSurface) {
	switch (movementDir) 
	{	
		case MOVEMENT_NONE:
			//current_anim = &
			idle_anim.passTime(0.03f);
			idle_anim.drawTo(screenSurface, x, y);
			break;
		
		case MOVEMENT_RIGHT:
			mv_right_anim.passTime(0.03f);
			mv_right_anim.drawTo(screenSurface, x, y);
			break;
			
		case MOVEMENT_UP:
			mv_up_anim.passTime(0.03f);
			mv_up_anim.drawTo(screenSurface, x, y);
			break;
			
		case MOVEMENT_DOWN:
			mv_down_anim.passTime(0.03f);
			mv_down_anim.drawTo(screenSurface, x, y);
			break;
			
		case MOVEMENT_LEFT:
			mv_left_anim.passTime(0.03f);
			mv_left_anim.drawTo(screenSurface, x, y);
			break;
			
		default:
			printf("Weird!! Don't know which animation to show!\n");
			break;
	}
}

PlayerSprite::~PlayerSprite() 
{

}