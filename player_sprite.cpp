#include "player_sprite.h"

PlayerSprite::PlayerSprite(float xCoord, float yCoord, TextureAtlas* textureAtlas) {
	printf("Creating sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;

	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 8;
	hitboxOffsetY = 4;
	hitbox.w = 30;
	hitbox.h = 44;
	
	idle_anim.init(textureAtlas, PLAYER_IDLE, 1, 100);
	mv_up_anim.init(textureAtlas, PLAYER_MVUP, 4, 100);
	mv_down_anim.init(textureAtlas, PLAYER_MVDOWN, 4, 100);
	mv_left_anim.init(textureAtlas, PLAYER_MVLEFT, 4, 100);
	mv_right_anim.init(textureAtlas, PLAYER_MVRIGHT, 4, 100);
	
	current_anim = &idle_anim;
	
	// create inventory with capacity 30
	inventory = new Inventory(30);
	
	fullHp = 100;
	currHp = 100;
}

bool PlayerSprite::handleKeyEvent(SDL_Event e) 
{
	// player pressed a key
	if (e.type == SDL_KEYDOWN)  // todo: E: inventory, R reload, F action, Q drop
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
				
			// interact key
			case SDLK_f:
				if (!interactPressed)
				{
					interactPressed = true;
					interactHandled = false;
					printf("Started Interact Request\n");
				}
				return true;

			// use in-hand inventory item
			case SDLK_SPACE: {
				inventory->useInHand(hitbox);
				Action* action = inventory->getAction();
				Action* buff = inventory->getBuff();
				Attack* attack = inventory->getAttack();
				if (attack)
				{
					printf("Adding attack\n");
					attacks.push_back(attack);	
				}
				return true;
			}
				
			// cycle in-hand inventory item forward
			case SDLK_TAB:
				inventory->cycleInHandFwd();
				return true;
				
			// drops item in-hand
			case SDLK_q: {
				Item* drop = inventory->removeInHand();
				drop->setPosition(x, y);
				drops.push_back(drop);
				return true;
			}
				
			default:
				return false;
		}
	}
	// player released a key
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym) 
		{
			case SDLK_RIGHT: // todo: support bi-directionality
			case SDLK_UP:
			case SDLK_LEFT:
			case SDLK_DOWN:
				changeDir(MOVEMENT_NONE);
				return true;

			case SDLK_f:
				interactPressed = false;
				printf("Stopped Interaction Request \n");
				return true;
				
			default:
				return false;
		}
	}
	// player rolled mouse wheel
	else if (e.type == SDL_MOUSEWHEEL)
	{
		// user scrolled up: cycle in-hand inventory item forward
		if (e.wheel.y == 1)
		{
			inventory->cycleInHandFwd();
		}
		// user scrolled down: cycle in-hand inventory item backward
		else 
		{
			inventory->cycleInHandBck();
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
			// no movement: simply pause animation that was playing. This way, the sprite remains
			// facing the same direction
			case MOVEMENT_NONE:
				//current_anim = &idle_anim;
				current_anim->pause();
				break;

			case MOVEMENT_RIGHT:
				current_anim = &mv_right_anim;
				current_anim->play();
				break;

			case MOVEMENT_UP:
				current_anim = &mv_up_anim;
				current_anim->play();
				break;

			case MOVEMENT_DOWN:
				current_anim = &mv_down_anim;
				current_anim->play();
				break;

			case MOVEMENT_LEFT:
				current_anim = &mv_left_anim;
				current_anim->play();
				break;

			default:
				printf("Weird!! Don't know which animation to show!\n");
				break;
		}
	}
}

void PlayerSprite::update(int ms) {
	(*current_anim).passTime(ms);
	if (currAction && !currAction->apply(this, ms)) // todo: should Actions be called from the Map/GameDriver?
	{
		delete(currAction);	
		currAction = NULL;
	}
}

void PlayerSprite::drawTo(SDL_Surface* screenSurface, int offsetX, int offsetY) {
	// draw current animation frame to screen
	(*current_anim).drawTo(screenSurface, x - offsetX, y - offsetY);
}

SDL_Point PlayerSprite::getPosition() 
{
	switch (movementDir) 
	{
		case MOVEMENT_NONE:
			return SDL_Point {(int) x + current_anim->frameWidth / 2, (int) y + current_anim->frameHeight };
			
		case MOVEMENT_UP:
			return SDL_Point {(int) x + current_anim->frameWidth / 2, (int) y + (int) (current_anim->frameHeight * 0.7f) };
			
		case MOVEMENT_DOWN:
			return SDL_Point {(int) x + current_anim->frameWidth / 2, (int) y + current_anim->frameHeight };
		
		case MOVEMENT_LEFT:
			return SDL_Point {(int) x, (int) y + current_anim->frameHeight };

		case MOVEMENT_RIGHT:
			return SDL_Point {(int) x + current_anim->frameWidth, (int) y + current_anim->frameHeight };
		
		default:
			printf("This shouldn't happen");
			return SDL_Point {-1, -1 };
	}
}

PlayerSprite::~PlayerSprite() 
{

}