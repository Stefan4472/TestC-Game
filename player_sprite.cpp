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

	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 8;
	hitboxOffsetY = 4;
	hitbox.w = 30;
	hitbox.h = 44;
	
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
		switch (e.key.keysym.sym) // todo: E: inventory, R reload, F action
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
	// save current position
	lastX = x;
	lastY = y;
	
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

void PlayerSprite::moveBack() 
{
	printf("Moving back to %f, %f from %f, %f\n", lastX, lastY, x, y);
	x = lastX;
	y = lastY;

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

float PlayerSprite::getPosX() 
{
	switch (movementDir) 
	{
		case MOVEMENT_NONE:
		case MOVEMENT_UP:
		case MOVEMENT_DOWN:
			return x + current_anim->frameWidth / 2;
		
		case MOVEMENT_LEFT:
			return x;

		case MOVEMENT_RIGHT:
			return x + current_anim->frameWidth;
		
		default:
			printf("This shouldn't happen");
			return x;
	}
}

float PlayerSprite::getPosY()
{
	switch (movementDir) 
	{
		case MOVEMENT_NONE:
		case MOVEMENT_LEFT:
		case MOVEMENT_RIGHT:
			return y + current_anim->frameHeight;
			
		case MOVEMENT_UP:
			return y + current_anim->frameHeight * 0.7f;
			
		case MOVEMENT_DOWN:
			return y + current_anim->frameHeight;
		
		default:
			printf("This shouldn't happen");
			return x;
	}
}

PlayerSprite::~PlayerSprite() 
{

}