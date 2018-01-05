#include "sprite.h"

void Sprite::move(int ms)
{
	if (movementDir == MOVEMENT_RIGHT) {
		x += ms * speedPerMs;
	} else if (movementDir == MOVEMENT_LEFT) {
		x -= ms * speedPerMs;
	}

	if (movementDir == MOVEMENT_UP) {
		y -= ms * speedPerMs;
	} else if (movementDir == MOVEMENT_DOWN) {
		y += ms * speedPerMs;
	}	
	hitbox.x = x + hitboxOffsetX;
	hitbox.y = y + hitboxOffsetY;
}

void Sprite::changeDir(int newDir)
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

void Sprite::update(int ms) {
	(*current_anim).passTime(ms);
}