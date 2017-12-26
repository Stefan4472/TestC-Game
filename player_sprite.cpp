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

	// note: this depends on the image of the sprite, and will need to be adjusted at times.
	hitboxOffsetX = 17;
	hitboxOffsetY = 11;
	hitbox.w = 100;
	hitbox.h = 134;
	
	idle_anim.init(idle_anim_sheet, 2, 100);
	mv_up_anim.init(mv_up_anim_sheet, 4, 100);
	mv_down_anim.init(mv_down_anim_sheet, 4, 100);
	mv_left_anim.init(mv_left_anim_sheet, 4, 100);
	mv_right_anim.init(mv_right_anim_sheet, 4, 100);
	
	current_anim = &idle_anim;
}

bool PlayerSprite::handleKeyEvent(SDL_Event e) 
{
	printf("PlayerSprite attempting to handle KeyEvent\n");
	
	// player pressed a key
	if (e.type == SDL_KEYDOWN) 
	{
		switch( e.key.keysym.sym )
		{ 
			case SDLK_RIGHT:
				changeDir(MOVEMENT_RIGHT);
				return true;					

			case SDLK_UP:
				changeDir(MOVEMENT_UP);
				return true;

			case SDLK_LEFT:
				changeDir(MOVEMENT_LEFT);
				return true;

			case SDLK_DOWN:
				changeDir(MOVEMENT_DOWN);
				return true;

			default:
				return false;
		}
	}
	// player released a key
	else
	{
		switch (e.key.keysym.sym) 
		{
			case SDLK_RIGHT: // todo: support bi-directionality
				//changeDir(-MOVEMENT_RIGHT);
				
			case SDLK_UP:
				//changeDir(-MOVEMENT_UP);
				
			case SDLK_LEFT:
				//changeDir(-MOVEMENT_LEFT);
				
			case SDLK_DOWN:
				//changeDir(-MOVEMENT_DOWN);
				changeDir(MOVEMENT_NONE);
				return true;

			default:
				return false;
		}
	} 
}

void PlayerSprite::move(int ms) {
	if (movementDir == MOVEMENT_RIGHT) {
		x += SPEED_CAP;
	} else if (movementDir == MOVEMENT_LEFT) {
		x -= SPEED_CAP;
	}

	if (movementDir == MOVEMENT_UP) {
		y -= SPEED_CAP;
	} else if (movementDir == MOVEMENT_DOWN) {
		y += SPEED_CAP;
	}	
	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
}

void PlayerSprite::changeDir(int newDir) {
	// only change if direction has been changed
	if (newDir != movementDir) {
		printf("Movement Change to %d\n", newDir);
		
		// reset currently-playing animation
		(*current_anim).reset();
		
		movementDir = newDir;
		
		switch (movementDir) 
		{	
			case MOVEMENT_NONE:
				current_anim = &idle_anim;
				break;

			case MOVEMENT_RIGHT:
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

void PlayerSprite::update(int ms) {
	(*current_anim).passTime(ms);
}

void PlayerSprite::drawTo(SDL_Surface* screenSurface, int offsetX, int offsetY) {
	// draw current animatino frame to screen
	(*current_anim).drawTo(screenSurface, x - offsetX, y - offsetY);
}

PlayerSprite::~PlayerSprite() 
{

}