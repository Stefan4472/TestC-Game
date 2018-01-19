#include "player_sprite.h"

PlayerSprite::PlayerSprite(float xCoord, float yCoord, TextureAtlas* textureAtlas, SDL_Renderer* renderer, TTF_Font* HUDFont) {
	printf("Creating sprite at %f, %f\n", xCoord, yCoord);
	
	x = xCoord;
	y = yCoord;
	
	this->renderer = renderer;

	// note: this depends on the image of the sprite, and will need to be adjusted at times. Also: hitboxes corresponding to frames of spritesheets
	hitboxOffsetX = 10;
	hitboxOffsetY = 44;
	hitbox.w = 32;
	hitbox.h = 13;
	
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
	
	headsUpDisplay = new PlayerHUD(renderer, HUDFont, NULL, currHp, fullHp);
	inventory->setInventoryListener(this);
}

void PlayerSprite::onInHandItemChanged(Item* newItem)
{
	printf("Received callback\n");	
	headsUpDisplay->updateItem(renderer, newItem);
}

bool PlayerSprite::handleKeyEvent(SDL_Event e) 
{
	// player pressed a key TODO: IGNORE REPEATED SIGNALS
	if (e.type == SDL_KEYDOWN)  // todo: E: inventory, R reload, F action, Q drop
	{
		switch( e.key.keysym.sym )
		{ 
			case SDLK_RIGHT:
				changeDir(DIRECTION_RIGHT);
				return true;					

			case SDLK_UP:
				changeDir(DIRECTION_UP);
				return true;

			case SDLK_LEFT:
				changeDir(DIRECTION_LEFT);
				return true;

			case SDLK_DOWN:
				changeDir(DIRECTION_DOWN);
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
				inventory->useInHand(getRightHandPosition(), facingDir);
				Action* action = inventory->getAction();
				if (action)
				{
					printf("Received action\n");
					// todo: add action
				}
				Action* buff = inventory->getBuff();
				if (buff)
				{
					printf("Received buff\n");
					buffs.push_back(buff);
				}
				Attack* attack = inventory->getAttack();
				if (attack)
				{
					printf("Adding attack\n");
					attacks.push_back(attack);	
				}
				return true;
			}
				
			// cycle in-hand inventory item forward and update HUD
			case SDLK_TAB:
				inventory->cycleInHandFwd(); // TODO: NEED A LISTENER FOR INVENTORY IN-HAND CHANGES
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
				changeDir(DIRECTION_NONE);
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
	
	if (movementDir == DIRECTION_RIGHT) {
		x += ms * PX_PER_MS;
	} else if (movementDir == DIRECTION_LEFT) {
		x -= ms * PX_PER_MS;
	}

	if (movementDir == DIRECTION_UP) {
		y -= ms * PX_PER_MS;
	} else if (movementDir == DIRECTION_DOWN) {
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
			case DIRECTION_NONE:
				//current_anim = &idle_anim;
				current_anim->pause();
				break;

			case DIRECTION_RIGHT:
				current_anim = &mv_right_anim;
				current_anim->play();
				facingDir = DIRECTION_RIGHT;
				break;

			case DIRECTION_UP:
				current_anim = &mv_up_anim;
				current_anim->play();
				facingDir = DIRECTION_UP;
				break;

			case DIRECTION_DOWN:
				current_anim = &mv_down_anim;
				current_anim->play();
				facingDir = DIRECTION_DOWN;
				break;

			case DIRECTION_LEFT:
				current_anim = &mv_left_anim;
				current_anim->play();
				facingDir = DIRECTION_LEFT;
				break;

			default:
				printf("Weird!! Don't know which animation to show!\n");
				break;
		}
	}
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
			printf("Weird!! Don't know which animation to show!\n");
			break;
	}
}

void PlayerSprite::handleAttacked(Attack* attack) 
{
	printf("Player Attacked\n");
}

void PlayerSprite::update(int ms) {
	(*current_anim).passTime(ms);
	if (currAction && !currAction->apply(this, ms)) // todo: should Actions be called from the Map/GameDriver?
	{
		delete(currAction);	
		currAction = NULL;
	}
}

/*void PlayerSprite::onInHandChanged()
{
	printf("Detected Changed to in-hand item\n");
}*/

void PlayerSprite::drawTo(SDL_Renderer* renderer, int offsetX, int offsetY) {
	// draw current animation frame to screen
	(*current_anim).drawTo(renderer, x - offsetX, y - offsetY);
	
	// draw in-hand item (if any)
	Item* in_hand = inventory->getInHand();
	if (in_hand)
	{
		SDL_Point hand_location = getRightHandPosition();
		in_hand->drawTo(renderer, (int) (hand_location.x - offsetX), (int) (hand_location.y - offsetY));
	}
}

void PlayerSprite::drawHUD(SDL_Renderer* renderer)
{
	headsUpDisplay->drawTo(renderer);
}


PlayerSprite::~PlayerSprite() 
{
	renderer = NULL;
}